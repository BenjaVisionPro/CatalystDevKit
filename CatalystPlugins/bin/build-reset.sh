#!/usr/bin/env bash
set -euo pipefail

# Always use the directory this script lives in
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

CLEAN="$SCRIPT_DIR/build-clean.sh"
GEN="$SCRIPT_DIR/generateProjectFiles.sh"

[[ -x "$CLEAN" ]] || { echo "❌ Missing or non-executable: $CLEAN"; exit 1; }
[[ -x "$GEN"   ]] || { echo "❌ Missing or non-executable: $GEN";   exit 1; }

echo "🧼 Running build-clean..."
"$CLEAN" ${1+"$@"}

echo
echo "🔧 Regenerating project files..."
"$GEN"   ${1+"$@"}

echo
echo "✅ Build reset complete."