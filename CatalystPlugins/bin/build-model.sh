#!/usr/bin/env bash
set -euo pipefail

# ---------------------------------------------
# build-models.sh
# Generates model assets from JSON for a plugin,
# using the CFGenerateModelAssets commandlet.
#
# Defaults are tailored for CatalystEcosystem.
#
# Usage:
#   bin/build-models.sh [-p PluginName] [-a /Script/Module.AssetClass] \
#                       [-i InputDirRel] [--ue-editor /path/to/UnrealEditor-Cmd] \
#                       [--dry-run] [--no-overwrite]
#
# Examples:
#   bin/build-models.sh
#   bin/build-models.sh -p CatalystEcosystem -a /Script/CatalystEcosystem.CEModelAsset
# ---------------------------------------------

# Resolve <project_dir> from this script location (…/bin/build-models.sh)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Find the .uproject (assumes one at repo root named CatalystPlugins.uproject)
UPROJECT="$PROJECT_DIR/CatalystPlugins.uproject"
if [[ ! -f "$UPROJECT" ]]; then
  echo "ERROR: Could not find .uproject at: $UPROJECT" >&2
  exit 1
fi

# Defaults (tuned for CatalystEcosystem)
PLUGIN_NAME="CatalystEcosystem"
ASSET_CLASS="/Script/CatalystEcosystem.CEModelAsset"
INPUT_DIR="Model"
OVERWRITE=1
DRYRUN=0

# Locate UnrealEditor-Cmd:
# 1) --ue-editor arg
# 2) UE_EDITOR env var
# 3) common macOS path used in your setup
UE_EDITOR_DEFAULT="/Users/jupiter/UnrealEngine/UE_5.7/Engine/Binaries/Mac/UnrealEditor-Cmd"
UE_EDITOR="${UE_EDITOR:-$UE_EDITOR_DEFAULT}"

print_usage() {
  cat <<EOF
Usage: $(basename "$0") [options]

Options:
  -p, --plugin <Name>            Plugin name (default: $PLUGIN_NAME)
  -a, --asset-class <Path>       Asset class path (default: $ASSET_CLASS)
  -i, --input-dir <RelPath>      Relative path under plugin root to scan for JSON (default: $INPUT_DIR)
      --ue-editor <Path>         Full path to UnrealEditor-Cmd (default: $UE_EDITOR)
      --dry-run                  Parse/import but do not save uassets
      --no-overwrite             Skip existing assets (don't replace)
  -h, --help                     Show this help

Example:
  $(basename "$0") -p CatalystEcosystem -a /Script/CatalystEcosystem.CEModelAsset
EOF
}

# Parse args
while (( "$#" )); do
  case "$1" in
    -p|--plugin)
      PLUGIN_NAME="$2"; shift 2;;
    -a|--asset-class)
      ASSET_CLASS="$2"; shift 2;;
    -i|--input-dir)
      INPUT_DIR="$2"; shift 2;;
    --ue-editor)
      UE_EDITOR="$2"; shift 2;;
    --dry-run)
      DRYRUN=1; shift;;
    --no-overwrite)
      OVERWRITE=0; shift;;
    -h|--help)
      print_usage; exit 0;;
    *)
      echo "Unknown option: $1" >&2; print_usage; exit 1;;
  esac
done

# Validate UE editor path
if [[ ! -x "$UE_EDITOR" ]]; then
  echo "ERROR: UnrealEditor-Cmd not found/executable at: $UE_EDITOR" >&2
  echo "       Provide via --ue-editor or UE_EDITOR env var." >&2
  exit 1
fi

# Build commandlet args
ARGS=(
  "$UPROJECT"
  -run=CFGenerateModelAssets
  "-Plugin=$PLUGIN_NAME"
  "-AssetClass=$ASSET_CLASS"
  "-InputDir=$INPUT_DIR"
)

(( OVERWRITE == 1 )) && ARGS+=( -Overwrite )
(( DRYRUN    == 1 )) && ARGS+=( -DryRun )

echo "==> Running CFGenerateModelAssets"
echo "    UPROJECT    : $UPROJECT"
echo "    UE_EDITOR   : $UE_EDITOR"
echo "    Plugin      : $PLUGIN_NAME"
echo "    AssetClass  : $ASSET_CLASS"
echo "    InputDir    : $INPUT_DIR"
echo "    Overwrite   : $OVERWRITE"
echo "    DryRun      : $DRYRUN"
echo

# Execute
exec "$UE_EDITOR" "${ARGS[@]}"