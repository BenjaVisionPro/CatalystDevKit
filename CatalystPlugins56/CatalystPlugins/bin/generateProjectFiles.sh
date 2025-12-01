#!/usr/bin/env bash
set -euo pipefail

# Auto-locate engine and project
ENGINE_ROOT="${ENGINE_ROOT:-$HOME/UnrealEngine/UE_5.6}"
PROJECT_ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
UPROJECT="$PROJECT_ROOT/CatalystPlugins/CatalystPlugins.uproject"

# Sanity checks
[[ -d "$ENGINE_ROOT" ]]   || { echo "❌ Engine not found: $ENGINE_ROOT"; exit 1; }
[[ -f "$UPROJECT" ]]      || { echo "❌ .uproject not found: $UPROJECT"; exit 1; }

echo "🚧 Generating project files..."
"$ENGINE_ROOT/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" \
  -project="$UPROJECT" -game

echo "✅ Done."