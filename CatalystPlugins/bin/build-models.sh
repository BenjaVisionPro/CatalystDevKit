#!/usr/bin/env bash
set -euo pipefail

# ---------------------------------------------
# build-models.sh
# Rebuilds model assets for ALL Catalyst plugins
# by calling bin/build-model.sh for each.
#
# Add new plugins to the PLUGINS array below.
# ---------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_SINGLE="$SCRIPT_DIR/build-model.sh"

if [[ ! -x "$BUILD_SINGLE" ]]; then
  echo "ERROR: build-model.sh not found/executable at: $BUILD_SINGLE" >&2
  exit 1
fi

# ----------------------------------------------------------------
# List of plugin configurations.
# Format: "PluginName:/Script/Module.AssetClass"
# ----------------------------------------------------------------
PLUGINS=(
  "CatalystEcosystem:/Script/CatalystEcosystem.CEModelAsset"
  # Add more as you grow:
  # "CatalystEconomy:/Script/CatalystEconomy.EcoModelAsset"
  # "CatalystWeather:/Script/CatalystWeather.WeatherModelAsset"
)

# Global flags forwarded to build-model.sh (optional).
# Leave empty for defaults; examples:
#   FLAGS=(--no-overwrite)
#   FLAGS=(--dry-run)
FLAGS=()

for entry in "${PLUGINS[@]}"; do
  PLUGIN="${entry%%:*}"
  ASSET_CLASS="${entry#*:}"

  echo
  echo "=== Building model for $PLUGIN ($ASSET_CLASS) ==="

  # Safe expansion: only pass FLAGS if there are any
  if ((${#FLAGS[@]})); then
    "$BUILD_SINGLE" -p "$PLUGIN" -a "$ASSET_CLASS" "${FLAGS[@]}"
  else
    "$BUILD_SINGLE" -p "$PLUGIN" -a "$ASSET_CLASS"
  fi
done

echo
echo "=== All plugin models processed. ==="