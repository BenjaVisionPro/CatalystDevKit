#!/usr/bin/env bash
set -euo pipefail

PROGNAME="$0"
. private/shFeedback
start_banner

# Defaults
registryName="$(/bin/hostname)"
stoneName=""
gemstoneVersion=""

# Parse args
positional=()
for arg in "$@"; do
  case "$arg" in
    --registry=*)
      registryName="${arg#--registry=}"
      ;;
    -h|--help)
      echo "Usage: $PROGNAME [--registry=<name>] <gemstoneVersion> <stoneName>"
      exit 0
      ;;
    *)
      positional+=("$arg")
      ;;
  esac
done

if [[ ${#positional[@]} -ne 2 ]]; then
  echo "ERROR: Need exactly 2 positional args: <gemstoneVersion> <stoneName>" >&2
  echo "Usage: $PROGNAME [--registry=<name>] <gemstoneVersion> <stoneName>" >&2
  exit 2
fi

gemstoneVersion="${positional[0]}"
stoneName="${positional[1]}"

# Save current directory
workingDirectory="$(pwd)"

# Setup the BenjaVision Catalyst development environment
information_banner "Version Report"
versionReport.solo

information_banner "Creating Registry $registryName"
createRegistry.solo "$registryName"

information_banner "Register Shared Product Directory $STONES_HOME/gemstone"
registerProductDirectory.solo --registry="$registryName" --productDirectory="$STONES_HOME/gemstone"

information_banner "Installing GemStone $gemstoneVersion"
downloadGemStone.solo --registry="$registryName" "$gemstoneVersion"
updateClientLibs.solo --registry="$registryName" "$gemstoneVersion"

information_banner "Registering GemStone $gemstoneVersion"
registerProduct.solo --registry="$registryName" --fromDirectory="$STONES_HOME/gemstone"

information_banner "Creating Project Directory $STONES_HOME/$stoneName"
projectPath="$STONES_HOME/$stoneName"
mkdir -p "$projectPath/git"

information_banner "Registering Project Git Directory $STONES_HOME/$stoneName/git"
registerProjectDirectory.solo --registry="$registryName" --projectDirectory="$projectPath/git"

information_banner "Creating Project Stones Directory $STONES_HOME/$stoneName/stones"
mkdir -p "$projectPath/stones"
registerStonesDirectory.solo --registry="$registryName" \
  --stonesDirectory="$projectPath/stones"

information_banner "Creating Stone $stoneName"
createStone.solo --registry="$registryName" --template=default_rowan3 "$stoneName" "$gemstoneVersion"

case "${OSTYPE:-}" in
  darwin*)
    warning_banner "Disabling Native Code for stone $stoneName"
    {
      echo "GEM_NATIVE_CODE_ENABLED=0;";
    } >> "$STONES_HOME/$stoneName/stones/$stoneName/gem.conf"
    cat "$STONES_HOME/$stoneName/stones/$stoneName/gem.conf"
    ;;
esac

information_banner "Setting ROWAN_PROJECTS_HOME"
export ROWAN_PROJECTS_HOME="$projectPath/git"
updateCustomEnv.solo --registry="$registryName" "$stoneName" \
  --addKey=ROWAN_PROJECTS_HOME --value="$ROWAN_PROJECTS_HOME" --restart

information_banner "Starting Stone $stoneName"
startStone.solo --registry="$registryName" "$stoneName" -b
gslist.solo -l

information_banner "Installing in stone $stoneName"
cd "$projectPath/stones/$stoneName"

# turn on unicodeComparisonMode required by Jadeite
enableUnicodeCompares.topaz -lq

information_banner "installing gt4GemStone"
installProject.stone "file:/opt/git/feenkcom/gt4gemstone/rowan/specs/gt4gemstone.ston" \
  --projectsHome="$projectPath/git/gt4gemstone" -D

# Restore working directory
cd "$workingDirectory"