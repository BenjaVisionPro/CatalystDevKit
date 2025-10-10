#!/usr/bin/env bash
set -euo pipefail

# Create a new Catalyst plugin from the neutral template by replacing tokens:
#   __PLUGIN_NAME__  -> <Name>   (e.g., CatalystLandscape)
#   __PREFIX__       -> <UPrefix> (e.g., CL)
#   __prefix__       -> <lprefix> (e.g., cl)
#
# Usage:
#   bin/new-plugin.sh --name CatalystLandscape --prefix CL
#   [--template CatalystPlugins/Plugins/CatalystPluginTemplate]
#   [--dest CatalystPlugins/Plugins]
#   [--dry-run]

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
TEMPLATE_DIR_DEFAULT="CatalystPlugins/Plugins/CatalystPluginTemplate"
DEST_DIR_DEFAULT="CatalystPlugins/Plugins"

NEW_NAME=""
NEW_PREFIX=""
TEMPLATE_DIR=""
DEST_PLUGINS_DIR=""
DRY_RUN=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --name)     NEW_NAME="$2"; shift 2 ;;
    --prefix)   NEW_PREFIX="$2"; shift 2 ;;
    --template) TEMPLATE_DIR="$2"; shift 2 ;;
    --dest)     DEST_PLUGINS_DIR="$2"; shift 2 ;;
    --dry-run)  DRY_RUN=1; shift 1 ;;
    -h|--help)
      echo "Usage: $0 --name <PluginName> --prefix <UPrefix> [--template <dir>] [--dest <dir>] [--dry-run]"
      exit 0 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

[[ -n "${NEW_NAME:-}"   ]] || { echo "Missing --name"; exit 1; }
[[ -n "${NEW_PREFIX:-}" ]] || { echo "Missing --prefix"; exit 1; }

TEMPLATE_DIR="${TEMPLATE_DIR:-$TEMPLATE_DIR_DEFAULT}"
DEST_PLUGINS_DIR="${DEST_PLUGINS_DIR:-$DEST_DIR_DEFAULT}"

TPL="$ROOT/$TEMPLATE_DIR"
OUT="$ROOT/$DEST_PLUGINS_DIR/$NEW_NAME"

[[ -d "$TPL" ]] || { echo "Template not found: $TPL"; exit 1; }
[[ ! -e "$OUT" ]] || { echo "Destination already exists: $OUT"; exit 1; }

LOWER_PREFIX="$(echo "$NEW_PREFIX" | tr 'A-Z' 'a-z')"

echo "== New Catalyst plugin =="
echo "Template : $TPL"
echo "Name     : $NEW_NAME"
echo "Prefix   : $NEW_PREFIX (lower: $LOWER_PREFIX)"
echo "Output   : $OUT"
[[ $DRY_RUN -eq 1 ]] && echo "(dry run)"

# 1) Copy template tree (excluding build cache dirs)
copy_template() {
  rsync -a --delete \
    --exclude='/Binaries' \
    --exclude='/Intermediate' \
    --exclude='/DerivedDataCache' \
    --exclude='/Saved' \
    "$TPL/" "$OUT/"
}
[[ $DRY_RUN -eq 1 ]] || copy_template

# 2) Rename paths containing tokens (deepest-first to avoid parent collisions)
rename_paths_token() {
  local base="$1" token="$2" repl="$3"
  # Gather matches
  IFS=$'\n' read -r -d '' -a hits < <(find "$base" -depth -name "*$token*" -print0 | xargs -0 -I{} bash -c 'echo "{}"' && printf '\0')
  # Sort by length desc (deepest first)
  IFS=$'\n' hits=($(for p in "${hits[@]}"; do [[ -n "$p" ]] && echo "${#p} $p"; done | sort -rn | cut -d" " -f2-))
  local p name dir newname newpath
  for p in "${hits[@]}"; do
    [[ -n "$p" ]] || continue
    name="$(basename "$p")"; dir="$(dirname "$p")"
    newname="${name//$token/$repl}"
    newpath="$dir/$newname"
    [[ "$p" == "$newpath" ]] && continue
    if [[ $DRY_RUN -eq 1 ]]; then
      echo "RENAME: $p -> $newpath"
    else
      mkdir -p "$dir"
      mv "$p" "$newpath"
    fi
  done
}

# Rename for ALL tokens in paths
rename_paths_token "$OUT" "__PLUGIN_NAME__" "$NEW_NAME"
rename_paths_token "$OUT" "__PREFIX__"      "$NEW_PREFIX"
rename_paths_token "$OUT" "__prefix__"      "$LOWER_PREFIX"

# 3) Rename the .uplugin (path rename above may have already done it; this is a safety)
if [[ -f "$OUT/__PLUGIN_NAME__.uplugin" ]]; then
  if [[ $DRY_RUN -eq 1 ]]; then
    echo "RENAME: $OUT/__PLUGIN_NAME__.uplugin -> $OUT/${NEW_NAME}.uplugin"
  else
    mv "$OUT/__PLUGIN_NAME__.uplugin" "$OUT/${NEW_NAME}.uplugin"
  fi
fi

# 4) Replace tokens inside files (skip binary-ish files)
is_binary() {
  case "${1##*.}" in
    uasset|umap|png|jpg|jpeg|dds|tga|bmp|psd|ico|icns|bin|pak|zip|7z|pdf|wav|mp3|ogg|mp4|mov|glb|gltf|fbx)
      return 0;;
  esac
  # Null byte sniff
  if head -c 4096 "$1" | LC_ALL=C grep -q $'\x00'; then
    return 0
  fi
  return 1
}

replace_tokens_in_file() {
  local f="$1"
  if is_binary "$f"; then
    return 0
  fi
  if [[ $DRY_RUN -eq 1 ]]; then
    echo "REPLACE: $f"
    return 0
  fi
  local R_NAME="${NEW_NAME//\//\\/}"
  local R_PREF="${NEW_PREFIX//\//\\/}"
  local R_LPREF="${LOWER_PREFIX//\//\\/}"
  # Single perl pass for all tokens
  perl -0777 -pe "s/__PLUGIN_NAME__/${R_NAME}/g; s/__PREFIX__/${R_PREF}/g; s/__prefix__/${R_LPREF}/g" -i -- "$f" || true
}

# Walk files
while IFS= read -r -d '' file; do
  replace_tokens_in_file "$file"
done < <(find "$OUT" -type f -print0)

echo
echo "✅ Done."
echo "Plugin : $OUT"
echo "Build  : \"\$ENGINE_ROOT/Engine/Build/BatchFiles/Mac/Build.sh\" UnrealEditor Mac Development -Project=\"\$PWD/CatalystPlugins/CatalystPlugins.uproject\""
echo "Tests  : bin/run-tests.sh --pattern \"${NEW_PREFIX}.*\" --tag \"${NEW_PREFIX}\""