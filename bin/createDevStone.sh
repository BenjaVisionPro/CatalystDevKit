#! /usr/bin/env sh
set -eu

PROGNAME=$0
SCRIPT_DIR=$(cd -- "$(dirname -- "$0")" 2>/dev/null && pwd)

# shellcheck disable=SC1091
. "${SCRIPT_DIR}/private/shFunctions"

# Load layered config (ENV > CWD/*.bvc > $BVC_CONF_DIR/bvc/bvc_defaults > bundled > safety net)
load_bvc_config

# ---------------------------------------------------------
# Required installer hooks (fatal if missing)
# These must define:
#   - install_devtools_projects <gitDir>
#   - install_projects <gitDir>
# Use CONF_DIR override first, then bundled fallback.
# ---------------------------------------------------------
# shellcheck disable=SC1090
. "$(conf_resolve 'projectSets/dev_tools.install.sh')"
# shellcheck disable=SC1090
. "$(conf_resolve 'projectSets/projects.install.sh')"

setup_traps
start_banner
information_banner "Create Development Stone"

# ---------------------------------------------------------
# Args (bvc calls with: --registry=NAME <gemstoneVersion> <stoneName>)
# ---------------------------------------------------------
registry=""
gemStoneVersion=""
stoneName=""

while [ $# -gt 0 ]; do
  case "$1" in
    --registry=*) registry=${1#*=} ;;
    --*)          error_banner "Unknown option: $1"
                  exit_1_banner "Usage: $(prog_basename "$PROGNAME") --registry=NAME <gemstoneVersion> <stoneName>   (called by bvc)" ;;
    *)
      if [ -z "$gemStoneVersion" ]; then
        gemStoneVersion="$1"
      elif [ -z "$stoneName" ]; then
        stoneName="$1"
      else
        error_banner "Too many positional arguments."
        exit_1_banner "Usage: $(prog_basename "$PROGNAME") --registry=NAME <gemstoneVersion> <stoneName>   (called by bvc)"
      fi
      ;;
  esac
  shift
done

if [ -z "$registry" ] || [ -z "$gemStoneVersion" ] || [ -z "$stoneName" ]; then
  error_banner "Missing required arguments."
  exit_1_banner "Usage: $(prog_basename "$PROGNAME") --registry=NAME <gemstoneVersion> <stoneName>   (called by bvc)"
fi

information_banner "Registry: ${registry}"
information_banner "Version : ${gemStoneVersion}"
information_banner "Stone   : ${stoneName}"

# ---------------------------------------------------------
# Sanity checks
# ---------------------------------------------------------
if [ -z "${STONES_HOME:-}" ] || [ ! -d "${STONES_HOME:-/nonexistent}" ]; then
  error_banner "STONES_HOME is not set or does not exist."
  exit_1_banner "Run 'bvc init' to set up GSDevKit before creating a stone."
fi

# ---------------------------------------------------------
# Local project layout (CWD-relative by design)
# ---------------------------------------------------------
workingDirectory="$(pwd)"
projectPath="${workingDirectory}"
stonesDir="${projectPath}/${GSDEVKIT_STONES_DIR}"
gitDir="$(abs_from_cwd "${ROWAN_PROJECTS_HOME}")"

# Resolve .ston project-set files (hard-fail if missing)
dev_tools_ston="$(conf_resolve 'projectSets/dev_tools.ston')"
projects_ston="$(conf_resolve 'projectSets/projects.ston')"

# ---------------------------------------------------------
# All-or-nothing existence check
# ---------------------------------------------------------
if registryReport.solo --registry="$registry" --stone="$stoneName" >/dev/null 2>&1; then
  information_banner "Stone '${stoneName}' already exists in registry '${registry}' — leaving it unchanged."
  information_banner "To recreate: stop the stone, delete its directory (in '${stonesDir}/${stoneName}' or '${STONES_HOME}/${stoneName}'), then rerun."
  exit_0_banner "Stone '${stoneName}' unchanged"
fi

# ---------------------------------------------------------
# Products (GemStone VM + client libs) and registration
# ---------------------------------------------------------
information_banner "Installing GemStone ${gemStoneVersion}"
downloadGemStone.solo   --registry="$registry" "$gemStoneVersion"
updateClientLibs.solo   --registry="$registry" "$gemStoneVersion"

information_banner "Registering GemStone ${gemStoneVersion}"
registerProduct.solo    --registry="$registry" --fromDirectory="${STONES_HOME}/gemstone"

# ---------------------------------------------------------
# Project sets (dev tools + user projects)
# ---------------------------------------------------------
information_banner "Creating IDE Tools Project Set from ${dev_tools_ston}"
createProjectSet.solo --registry="$registry" --projectSet=dev_tools \
  --from="${dev_tools_ston}"

information_banner "Creating User Project Set from ${projects_ston}"
createProjectSet.solo --registry="$registry" --projectSet=projects \
  --from="${projects_ston}"

# ---------------------------------------------------------
# Git directory (repositories)
# ---------------------------------------------------------
information_banner "Ensuring project git directory: ${gitDir}"
[ -d "${gitDir}" ] || mkdir -p "${gitDir}"

information_banner "Registering Project Git Directory: ${gitDir}"
registerProjectDirectory.solo --registry="$registry" --projectDirectory="${gitDir}"

information_banner "Cloning Projects from project set 'dev_tools'"
cloneProjectsFromProjectSet.solo --registry="$registry" --projectSet=dev_tools \
  --projectDirectory="${gitDir}"

information_banner "Cloning Projects from project set 'projects'"
cloneProjectsFromProjectSet.solo --registry="$registry" --projectSet=projects \
  --projectDirectory="${gitDir}"

# ---------------------------------------------------------
# Stones directory (where local stones live)
# ---------------------------------------------------------
information_banner "Ensuring stones directory: ${stonesDir}"
[ -d "${stonesDir}" ] || mkdir -p "${stonesDir}"

information_banner "Registering stones directory: ${stonesDir}"
registerStonesDirectory.solo --registry="$registry" --stonesDirectory="${stonesDir}"

# ---------------------------------------------------------
# Create the stone (template: default_rowan3)
# ---------------------------------------------------------
information_banner "Creating stone '${stoneName}' (template: default_rowan3)"
createStone.solo --registry="$registry" --template=default_rowan3 "$stoneName" "$gemStoneVersion"

# macOS: disable native code (JIT) for this stone
case "${OSTYPE:-}" in
  darwin*)
    warning_banner "Disabling Native Code for stone '${stoneName}' (macOS)"
    printf '%s\n' "GEM_NATIVE_CODE_ENABLED=0;" >> "${stonesDir}/${stoneName}/gem.conf"
    ;;
esac

# ---------------------------------------------------------
# Environment for tooling (ROWAN)
# ---------------------------------------------------------
information_banner "Setting ROWAN_PROJECTS_HOME=${gitDir}"
export ROWAN_PROJECTS_HOME="${gitDir}"
updateCustomEnv.solo --registry="$registry" "$stoneName" \
  --addKey=ROWAN_PROJECTS_HOME --value="$ROWAN_PROJECTS_HOME" --restart

# ---------------------------------------------------------
# Start the stone & show status
# ---------------------------------------------------------
information_banner "Starting stone '${stoneName}'"
startStone.solo --registry="$registry" "$stoneName" -b
gslist.solo -l || true

# ---------------------------------------------------------
# Load baseline projects into the stone
# ---------------------------------------------------------
cd "${stonesDir}/${stoneName}"

# Jadeite requirement: turn on unicodeComparisonMode
enableUnicodeCompares.topaz -lq

# Install Dev Tools (required hooks already loaded)
information_banner "Installing dev tools projects"
install_devtools_projects "${gitDir}"

# Install User Projects
information_banner "Installing user projects"
install_projects "${gitDir}"

# Restore working directory
cd "${workingDirectory}"

exit_0_banner "Stone '${stoneName}' created"