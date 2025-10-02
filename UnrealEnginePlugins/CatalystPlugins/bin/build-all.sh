#!/usr/bin/env bash
set -euo pipefail

# --- EDIT IF NEEDED ---
UE="/Users/jupiter/UnrealEngine/UE_5.6"
UPROJ="/opt/git/BenjaVision/CatalystDevKit/UnrealEnginePlugins/CatalystPlugins/CatalystPlugins.uproject"
TARGET_PLATFORMS="${TARGET_PLATFORMS:-Mac}"      # e.g. Mac, Win64, Linux, Mac,Win64
BUILD_CONFIG="${BUILD_CONFIG:-Development}"      # Development or Shipping
# ----------------------

PROJECT_DIR="$(cd "$(dirname "$UPROJ")" && pwd)"
PLUGINS_DIR="$PROJECT_DIR/Plugins"
PACKAGES_DIR="$PROJECT_DIR/../Packages"
mkdir -p "$PACKAGES_DIR"

echo "==> Building UnrealEditor ($BUILD_CONFIG) for warm cache"
"$UE/Engine/Build/BatchFiles/Mac/Build.sh" \
  UnrealEditor Mac "$BUILD_CONFIG" -Project="$UPROJ" -WaitMutex -NoHotReload

# Return dependency plugin NAMES from a .uplugin (unique, simple parse)
deps_of() {
  local uplugin="$1"
  sed -n '/"Plugins"[[:space:]]*:/,/\]/{p;}' "$uplugin" 2>/dev/null \
    | grep -oE '"Name"[[:space:]]*:[[:space:]]*"[^"]+"' \
    | sed -E 's/.*"Name"[[:space:]]*:[[:space:]]*"([^"]+)".*/\1/' \
    | sort -u
}

# Build one plugin by surfacing local deps via -AdditionalPluginDirectories=<leaf dir>
build_plugin() {
  local uplugin="$1"
  local name="$(basename "${uplugin%.*}")"
  local out="$PACKAGES_DIR/$name"

  # Collect local dependency leaf dirs that contain a .uplugin
  local dep_flags=()
  local deps
  deps="$(deps_of "$uplugin" || true)"
  if [ -n "${deps:-}" ]; then
    echo "-> $name deps: $deps"
    for dep in $deps; do
      local dep_dir="$PLUGINS_DIR/$dep"
      if [ -f "$dep_dir/$dep.uplugin" ]; then
        dep_flags+=("-AdditionalPluginDirectories=$dep_dir")
      fi
    done
  fi

  echo "-> Packaging $name"
  echo "   UAT: BuildPlugin -Plugin=\"$uplugin\" -Package=\"$out\" -TargetPlatforms=\"$TARGET_PLATFORMS\" ${dep_flags[*]} -Rocket"
  "$UE/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin \
    -Plugin="$uplugin" \
    -Package="$out" \
    -TargetPlatforms="$TARGET_PLATFORMS" \
    "${dep_flags[@]}" \
    -Rocket
}

echo "==> Discovering plugins in $PLUGINS_DIR"
# Find leaf *.uplugin files: Plugins/<Name>/<Name>.uplugin
# Avoid bashisms like mapfile for macOS /bin/bash
while IFS= read -r U; do
  [ -z "$U" ] && continue
  build_plugin "$U"
done < <(find "$PLUGINS_DIR" -maxdepth 2 -mindepth 2 -type f -name '*.uplugin' | sort)

echo "==> Done."