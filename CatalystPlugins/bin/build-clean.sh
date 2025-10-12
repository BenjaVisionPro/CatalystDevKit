#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"

echo "🧹 Cleaning CatalystDevKit at $ROOT"

# Core project directories to wipe
TARGETS=(
  "$ROOT/Binaries"
  "$ROOT/Intermediate"
  "$ROOT/DerivedDataCache"
  "$ROOT/Saved"
  "$ROOT/Build"
)

# Clean each plugin folder recursively
PLUGIN_ROOT="$ROOT/CatalystPlugins/Plugins"
if [[ -d "$PLUGIN_ROOT" ]]; then
  echo "🧩 Cleaning plugin build artifacts under $PLUGIN_ROOT..."
  while IFS= read -r -d '' d; do
    TARGETS+=("$d")
  done < <(find "$PLUGIN_ROOT" -type d \( -name "Binaries" -o -name "Intermediate" -o -name "Build" \) -print0)
fi

# Delete targets
for t in "${TARGETS[@]}"; do
  if [[ -d "$t" ]]; then
    echo "  ❌ Removing $t"
    rm -rf "$t"
  fi
done

# Optional IDE metadata cleanup
if [[ -d "$ROOT/.vs" ]]; then
  echo "  ❌ Removing .vs (Visual Studio metadata)"
  rm -rf "$ROOT/.vs"
fi

if [[ -d "$ROOT/.idea" ]]; then
  echo "  ❌ Removing .idea (Rider metadata)"
  rm -rf "$ROOT/.idea"
fi

echo "✅ Clean complete."