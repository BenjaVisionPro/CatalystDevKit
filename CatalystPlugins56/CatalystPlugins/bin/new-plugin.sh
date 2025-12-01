#!/usr/bin/env bash
set -euo pipefail

# Create a new Catalyst plugin by cloning the neutral template and replacing tokens:
#   __PLUGIN_NAME__        -> <Name>     (e.g., CatalystLandscape)
#   __PLUGIN_DISPLAY_NAME__-> <Name w/o leading 'Catalyst'> (e.g., Landscape)
#   __PREFIX__             -> <UPrefix>  (e.g., CL)
#   __prefix__             -> <lprefix>  (e.g., cl)
#   CATALYSTECOSYSTEM(S)?_API / __PLUGIN_API__               -> <PLUGINNAME>_API (UPPERCASE)
#   CATALYSTECOSYSTEM(S)?EDITOR_API / __PLUGIN_EDITOR_API__  -> <PLUGINNAME>EDITOR_API (UPPERCASE)
#
# Also updates the .uproject's "Plugins" list to include the new plugin (idempotent, via jq).

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
TEMPLATE_DIR_DEFAULT="CatalystPlugins/PluginTemplate/CatalystPluginTemplate"
DEST_DIR_DEFAULT="CatalystPlugins/Plugins"
UPROJECT_DEFAULT="CatalystPlugins/CatalystPlugins.uproject"

NEW_NAME=""
NEW_PREFIX=""
TEMPLATE_DIR=""
DEST_PLUGINS_DIR=""
UPROJECT_PATH=""
DRY_RUN=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --name)     NEW_NAME="$2"; shift 2 ;;
    --prefix)   NEW_PREFIX="$2"; shift 2 ;;
    --template) TEMPLATE_DIR="$2"; shift 2 ;;
    --dest)     DEST_PLUGINS_DIR="$2"; shift 2 ;;
    --uproject) UPROJECT_PATH="$2"; shift 2 ;;
    --dry-run)  DRY_RUN=1; shift 1 ;;
    -h|--help)
      echo "Usage: $0 --name <PluginName> --prefix <UPrefix> [--template <dir>] [--dest <dir>] [--uproject <file>] [--dry-run]"
      exit 0 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

[[ -n "${NEW_NAME:-}"   ]] || { echo "Missing --name"; exit 1; }
[[ -n "${NEW_PREFIX:-}" ]] || { echo "Missing --prefix"; exit 1; }

TEMPLATE_DIR="${TEMPLATE_DIR:-$TEMPLATE_DIR_DEFAULT}"
DEST_PLUGINS_DIR="${DEST_PLUGINS_DIR:-$DEST_DIR_DEFAULT}"
UPROJECT_PATH="${UPROJECT_PATH:-$UPROJECT_DEFAULT}"

TPL="$ROOT/$TEMPLATE_DIR"
OUT="$ROOT/$DEST_PLUGINS_DIR/$NEW_NAME"
UPROJECT_ABS="$ROOT/$UPROJECT_PATH"

[[ -d "$TPL" ]] || { echo "Template not found: $TPL"; exit 1; }
[[ ! -e "$OUT" ]] || { echo "Destination already exists: $OUT"; exit 1; }
[[ -f "$UPROJECT_ABS" ]] || { echo "uproject not found: $UPROJECT_ABS"; exit 1; }
command -v jq >/dev/null 2>&1 || { echo "jq is required but not found. Install jq and retry."; exit 1; }

LOWER_PREFIX="$(echo "$NEW_PREFIX" | tr 'A-Z' 'a-z')"
UPPER_PLUGIN_NAME="$(echo "$NEW_NAME" | tr '[:lower:]' '[:upper:]')"
UPPER_PLUGIN_API="${UPPER_PLUGIN_NAME}_API"
UPPER_PLUGIN_EDITOR_API="${UPPER_PLUGIN_NAME}EDITOR_API"

# Derive display name by stripping leading 'Catalyst' if present
if [[ "$NEW_NAME" == Catalyst* ]]; then
  PLUGIN_DISPLAY_NAME="${NEW_NAME#Catalyst}"
  [[ -z "$PLUGIN_DISPLAY_NAME" ]] && PLUGIN_DISPLAY_NAME="$NEW_NAME"
else
  PLUGIN_DISPLAY_NAME="$NEW_NAME"
fi

echo "== New Catalyst plugin =="
echo "Template  : $TPL"
echo "Name      : $NEW_NAME"
echo "Display   : $PLUGIN_DISPLAY_NAME"
echo "Prefix    : $NEW_PREFIX (lower: $LOWER_PREFIX)"
echo "API       : $UPPER_PLUGIN_API"
echo "API(Ed)   : $UPPER_PLUGIN_EDITOR_API"
echo "Output    : $OUT"
echo "UProject  : $UPROJECT_ABS"
[[ $DRY_RUN -eq 1 ]] && echo "(dry run)"

# 1) Copy template (exclude build junk)
if [[ $DRY_RUN -eq 0 ]]; then
  rsync -a --delete \
    --exclude='/Binaries' \
    --exclude='/Intermediate' \
    --exclude='/DerivedDataCache' \
    --exclude='/Saved' \
    "$TPL/" "$OUT/"
fi

# 2) Rename paths containing tokens (deepest-first; Bash 3–safe)
rename_paths_token() {
  local base="$1" token="$2" repl="$3"
  local tmp; tmp="$(mktemp -t ren.XXXXXX)"
  find "$base" -depth -name "*$token*" -print0 2>/dev/null \
  | while IFS= read -r -d '' p; do
      printf "%08d\t%s\n" "${#p}" "$p" >> "$tmp"
    done
  if [[ ! -s "$tmp" ]]; then rm -f "$tmp"; return 0; fi
  sort -rn "$tmp" | cut -f2- | while IFS= read -r p; do
    [[ -n "$p" && -e "$p" ]] || continue
    local dir name newname newpath
    dir="$(dirname "$p")" || continue
    name="$(basename "$p")" || continue
    newname="${name//$token/$repl}"
    newpath="$dir/$newname"
    [[ "$p" == "$newpath" ]] && continue
    if [[ $DRY_RUN -eq 1 ]]; then
      echo "RENAME: $p -> $newpath"
    else
      [[ -e "$p" ]] || continue
      mv "$p" "$newpath"
    fi
  done
  rm -f "$tmp"
}

# Rename all tokens in pathnames
rename_paths_token "$OUT" "__PLUGIN_NAME__"         "$NEW_NAME"
rename_paths_token "$OUT" "__PLUGIN_DISPLAY_NAME__" "$PLUGIN_DISPLAY_NAME"
rename_paths_token "$OUT" "__PREFIX__"              "$NEW_PREFIX"
rename_paths_token "$OUT" "__prefix__"              "$LOWER_PREFIX"

# 3) Rename the .uplugin (safety)
if [[ -f "$OUT/__PLUGIN_NAME__.uplugin" ]]; then
  if [[ $DRY_RUN -eq 1 ]]; then
    echo "RENAME: $OUT/__PLUGIN_NAME__.uplugin -> $OUT/${NEW_NAME}.uplugin"
  else
    mv "$OUT/__PLUGIN_NAME__.uplugin" "$OUT/${NEW_NAME}.uplugin"
  fi
fi

# 4) Replace tokens inside files (UE text extensions) + API macro fixes
replace_tokens_in_file() {
  local f="$1"
  if [[ $DRY_RUN -eq 1 ]]; then
    echo "REPLACE: $f"
    return 0
  fi
  local R_NAME="${NEW_NAME//\//\\/}"
  local R_DNAME="${PLUGIN_DISPLAY_NAME//\//\\/}"
  local R_PREF="${NEW_PREFIX//\//\\/}"
  local R_LPREF="${LOWER_PREFIX//\//\\/}"
  local R_API="${UPPER_PLUGIN_API//\//\\/}"
  local R_API_ED="${UPPER_PLUGIN_EDITOR_API//\//\\/}"
  perl -0777 -i -pe "
    s/__PLUGIN_NAME__/${R_NAME}/g;
    s/__PLUGIN_DISPLAY_NAME__/${R_DNAME}/g;
    s/__PREFIX__/${R_PREF}/g;
    s/__prefix__/${R_LPREF}/g;

    # Runtime API macros (donor + placeholder)
    s/\bCATALYSTECOSYSTEMS?_API\b/${R_API}/g;
    s/\b__PLUGIN_API__\b/${R_API}/g;

    # Editor API macros (donor + placeholder)
    s/\bCATALYSTECOSYSTEMS?EDITOR_API\b/${R_API_ED}/g;
    s/\b__PLUGIN_EDITOR_API__\b/${R_API_ED}/g;
  " "$f" || true
}

find "$OUT" -type f \( \
  -name '*.h' -o -name '*.hpp' -o -name '*.cpp' -o -name '*.inl' -o \
  -name '*.cs' -o -name '*.Build.cs' -o -name '*.Target.cs' -o \
  -name '*.uplugin' -o -name '*.uproject' -o \
  -name '*.json' -o -name '*.ini' -o -name '*.txt' -o -name '*.md' -o \
  -name '*.usf' -o -name '*.ush' \
\) -print0 \
| while IFS= read -r -d '' file; do
    replace_tokens_in_file "$file"
  done

# 5) Verify no tokens remain inside the new plugin
if grep -R -E '__PLUGIN_NAME__|__PLUGIN_DISPLAY_NAME__|__PREFIX__|__prefix__' "$OUT" >/dev/null 2>&1; then
  echo "❌ Tokens still present in $OUT"
  grep -R --line-number -E '__PLUGIN_NAME__|__PLUGIN_DISPLAY_NAME__|__PREFIX__|__prefix__' "$OUT" || true
  exit 1
fi

# 6) Update the .uproject Plugins array (idempotent; jq required)
if [[ $DRY_RUN -eq 1 ]]; then
  echo "UPROJECT: would add plugin \"$NEW_NAME\" to $UPROJECT_ABS"
else
  tmp="$(mktemp -t uproj.XXXXXX)"
  jq --arg name "$NEW_NAME" '
    .Plugins = (
      (.Plugins // [])
      | if any(.[]; .Name == $name) then . else . + [{ "Name": $name, "Enabled": true }] end
    )
  ' "$UPROJECT_ABS" > "$tmp" && mv "$tmp" "$UPROJECT_ABS"
fi

echo
echo "✅ Done."
echo "Plugin : $OUT"
echo "Build  : \"\$ENGINE_ROOT/Engine/Build/BatchFiles/Mac/Build.sh\" UnrealEditor Mac Development -Project=\"\$PWD/CatalystPlugins/CatalystPlugins.uproject\""
echo "Tests  : bin/run-tests.sh --pattern \"${NEW_PREFIX}.*\" --tag \"${NEW_PREFIX}\""