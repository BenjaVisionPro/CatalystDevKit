#!/usr/bin/env bash
set -euo pipefail

SUITES="${SUITES:-CF CE}"   # override via env or --suites "CF CE CC"
UPROJECT="${UPROJECT:-}"
UE_BIN="${UE_BIN:-}"
ENGINE_ROOT="${ENGINE_ROOT:-/Users/jupiter/UnrealEngine/UE_5.6}"

# ---- args ----
while [[ $# -gt 0 ]]; do
  case "$1" in
    --suites)   SUITES="$2"; shift 2 ;;
    --uproject) UPROJECT="$2"; shift 2 ;;
    --ue-bin)   UE_BIN="$2"; shift 2 ;;
    --engine-root) ENGINE_ROOT="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUN_ONE="$SCRIPT_DIR/run-tests.sh"

echo "Suites      : $SUITES"
echo "ENGINE_ROOT : $ENGINE_ROOT"
echo "UE_BIN      : ${UE_BIN:-<auto from ENGINE_ROOT>}"
echo "UPROJECT    : ${UPROJECT:-<auto-discover>}"
echo

FAILED=()
for S in $SUITES; do
  echo ""
  echo "==== Running suite: $S ===="
  if ENGINE_ROOT="$ENGINE_ROOT" UE_BIN="$UE_BIN" UPROJECT="$UPROJECT" \
     "$RUN_ONE" --pattern "${S}.*" --tag "$S"; then
    echo "✅ $S passed"
  else
    echo "❌ $S failed"
    FAILED+=("$S")
  fi
done

echo ""
if [[ ${#FAILED[@]} -gt 0 ]]; then
  echo "One or more suites failed: ${FAILED[*]}"
  exit 1
fi
echo "All suites passed."