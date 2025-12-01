#!/usr/bin/env bash
set -euo pipefail

# Usage: bin/clean.sh [--uproject /abs/path/to/CatalystPlugins.uproject]
UPROJECT=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --uproject) UPROJECT="$2"; shift 2 ;;
    -h|--help)  echo "Usage: $0 [--uproject /path/to/*.uproject]"; exit 0 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"

# Find a .uproject if not provided
if [[ -z "$UPROJECT" ]]; then
  UPROJECT="$(find "$ROOT" -maxdepth 4 -name "*.uproject" | head -n1 || true)"
fi
PROJECT_DIR="$ROOT"
if [[ -n "$UPROJECT" && -f "$UPROJECT" ]]; then
  PROJECT_DIR="$(cd "$(dirname "$UPROJECT")" && pwd)"
fi

echo "🧹 Clean:"
echo "  • repo root     : $ROOT"
echo "  • project root  : $PROJECT_DIR"
echo

# Remove common build dirs at a base path if present
clean_base() {
  local base="$1"
  for d in Binaries Intermediate DerivedDataCache Saved Build; do
    if [[ -d "$base/$d" ]]; then
      echo "  ❌ $base/$d"
      rm -rf "$base/$d"
    fi
  done
}

clean_base "$ROOT"
[[ "$PROJECT_DIR" != "$ROOT" ]] && clean_base "$PROJECT_DIR"

# Remove plugin build dirs (Binaries/Intermediate/Build) under given root
clean_plugins_under() {
  local plugroot="$1"
  [[ -d "$plugroot" ]] || return 0
  echo "🧩 Plugins under: $plugroot"
  find "$plugroot" -type d \( -name Binaries -o -name Intermediate -o -name Build \) -prune -print0 \
  | xargs -0 -I{} sh -c 'echo "  ❌ {}"; rm -rf "{}"'
}

clean_plugins_under "$ROOT/CatalystPlugins/Plugins"
clean_plugins_under "$PROJECT_DIR/Plugins"

# IDE metadata
echo "🧰 IDE metadata:"
if [[ -d "$ROOT/.vs" ]]; then echo "  ❌ $ROOT/.vs"; rm -rf "$ROOT/.vs"; fi
if [[ -d "$ROOT/.idea" ]]; then echo "  ❌ $ROOT/.idea"; rm -rf "$ROOT/.idea"; fi
if compgen -G "$ROOT"/*.xcworkspace > /dev/null; then echo "  ❌ $ROOT/*.xcworkspace"; rm -rf "$ROOT"/*.xcworkspace; fi
if compgen -G "$ROOT"/*.xcodeproj    > /dev/null; then echo "  ❌ $ROOT/*.xcodeproj";    rm -rf "$ROOT"/*.xcodeproj;    fi

if [[ "$PROJECT_DIR" != "$ROOT" ]]; then
  if [[ -d "$PROJECT_DIR/.vs" ]]; then echo "  ❌ $PROJECT_DIR/.vs"; rm -rf "$PROJECT_DIR/.vs"; fi
  if [[ -d "$PROJECT_DIR/.idea" ]]; then echo "  ❌ $PROJECT_DIR/.idea"; rm -rf "$PROJECT_DIR/.idea"; fi
  if compgen -G "$PROJECT_DIR"/*.xcworkspace > /dev/null; then echo "  ❌ $PROJECT_DIR/*.xcworkspace"; rm -rf "$PROJECT_DIR"/*.xcworkspace; fi
  if compgen -G "$PROJECT_DIR"/*.xcodeproj    > /dev/null; then echo "  ❌ $PROJECT_DIR/*.xcodeproj";    rm -rf "$PROJECT_DIR"/*.xcodeproj;    fi
fi

echo
echo "✅ Clean complete."