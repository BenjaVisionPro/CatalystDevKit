#!/usr/bin/env bash
set -euo pipefail

# Prefer the headless binary; fall back to the app bundle binary
DEFAULT_ENGINE_ROOT="${ENGINE_ROOT:-/Users/jupiter/UnrealEngine/UE_5.6}"
DEFAULT_UE_BIN_CMD="$DEFAULT_ENGINE_ROOT/Engine/Binaries/Mac/UnrealEditor"
DEFAULT_UE_BIN_APP="$DEFAULT_ENGINE_ROOT/Engine/Binaries/Mac/UnrealEditor.app/Contents/MacOS/UnrealEditor"

UPROJECT="${UPROJECT:-}"
UE_BIN="${UE_BIN:-}"
PATTERN="${PATTERN:-CF.*}"
TAG="${TAG:-}"   # optional subdir under CIReports (e.g., CF, CE)

# ---- args ----
while [[ $# -gt 0 ]]; do
  case "$1" in
    --uproject) UPROJECT="$2"; shift 2 ;;
    --ue-bin)   UE_BIN="$2"; shift 2 ;;
    --pattern)  PATTERN="$2"; shift 2 ;;
    --tag)      TAG="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel 2>/dev/null || echo "$SCRIPT_DIR/..")"

# ---- locate .uproject if not provided ----
if [[ -z "$UPROJECT" ]]; then
  CANDIDATES=()
  # Avoid mapfile (not in mac bash 3). Avoid sort -z (BSD sort).
  while IFS= read -r -d '' f; do CANDIDATES+=("$f"); done \
    < <(find "$REPO_ROOT" -maxdepth 4 -name "*.uproject" -print0)
  if [[ ${#CANDIDATES[@]} -eq 0 ]]; then
    echo "No .uproject found under $REPO_ROOT" >&2
    exit 1
  fi
  # Prefer CatalystPlugins.uproject if present
  for c in "${CANDIDATES[@]}"; do
    if [[ "$(basename "$c")" == "CatalystPlugins.uproject" ]]; then UPROJECT="$c"; break; fi
  done
  [[ -z "$UPROJECT" ]] && UPROJECT="${CANDIDATES[0]}"
fi

# ---- resolve UE binary ----
if [[ -z "$UE_BIN" ]]; then
  if [[ -x "$DEFAULT_UE_BIN_CMD" ]]; then
    UE_BIN="$DEFAULT_UE_BIN_CMD"
  elif [[ -x "$DEFAULT_UE_BIN_APP" ]]; then
    UE_BIN="$DEFAULT_UE_BIN_APP"
  fi
fi
if [[ ! -x "$UE_BIN" ]]; then
  echo "UE_BIN not executable: $UE_BIN" >&2
  echo "Set UE_BIN or use --ue-bin /path/to/UnrealEditor(-Cmd)" >&2
  exit 1
fi

UPROJECT_DIR="$(cd "$(dirname "$UPROJECT")" && pwd)"
BASE_OUT="$UPROJECT_DIR/Saved/Logs/CIReports"
OUT_DIR="$BASE_OUT"; [[ -n "$TAG" ]] && OUT_DIR="$BASE_OUT/$TAG"
mkdir -p "$OUT_DIR"
LOG_FILE="$OUT_DIR/AutomationTest.log"

echo "== Catalyst Tests =="
echo "UE_BIN   : $UE_BIN"
echo "UPROJECT : $UPROJECT"
echo "PATTERN  : $PATTERN"
echo "TAG      : ${TAG:-<none>}"
echo "LOG      : $LOG_FILE"
echo

# ---- run tests ----
"$UE_BIN" "$UPROJECT" \
  -unattended -nop4 -nosplash -NullRHI -NoSound -log -stdout \
  -ExecCmds="Automation RunTests $PATTERN; Automation DumpReports; Quit" \
  | tee "$LOG_FILE"

# ---- detect failures in summary ----
if grep -E "Fail(ed)?:\s*[1-9]" "$LOG_FILE" >/dev/null 2>&1; then
  echo "Automation tests reported failures."
  exit 1
fi

# ---- collect reports ----
AUTOMATION_DIR="$UPROJECT_DIR/Saved/Automation"
if [[ -d "$AUTOMATION_DIR" ]]; then
  if command -v rsync >/dev/null 2>&1; then
    rsync -a "$AUTOMATION_DIR"/ "$OUT_DIR/AutomationReports"/
  else
    mkdir -p "$OUT_DIR/AutomationReports"
    cp -R "$AUTOMATION_DIR"/. "$OUT_DIR/AutomationReports"/ 2>/dev/null || true
  fi
fi

echo "Automation tests passed."