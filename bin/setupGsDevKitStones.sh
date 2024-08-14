#! /usr/bin/env sh
PROGNAME=$0
set -e

. private/shFeedback
start_banner

usage() {
  cat << EOF >&2
Usage: $PROGNAME [-v[v]] [-p <parent_dir>] [-n <devKit_root_directory_name>]

 -p <dir>		the parent directory inside which the dev kit will be installed. Default /opt
 -n <subDir>	the name of the devKit root directory inside the <dir> directory. Default GsDevKit
 -v[vv]			verbose output

If no options are specified the devKit will be installed in /opt/stones
EOF
  exit 1
}

#===============================================
# Verbose level feedback
#===============================================
info() {
	local message="$1"
	local level=$2
	if [ $verbose_level -ge $level ];then
		information_banner "$message"
	fi
}

#===============================================
# Crete directory if it doesn't exist
#===============================================
conditionallyCreateDirectory() {
	local directoryPath="$1"
	if [ ! -d "$directoryPath" ]; then
		info "Creating $directoryPath" 1
		mkdir -p "$directoryPath"
	else
		info "$directoryPath already exists. If you want to recreate $directoryPath delete it and re-run this script." 1
	fi
}

#===============================================
# Setup
#===============================================

# Save current directory
workingDirectory=`PWD`

# ensure we are not running on windows
PLATFORM="`uname -sm | tr ' ' '-'`"
if [[ "$PLATFORM" == MINGW32_NT* || "$PLATFORM" == MSYS_NT* ]] ; then
  exit_1_banner "This script is a server-only script and cannot be used on Windows"
fi

# Parent directory in which to install everything. Defaults to /opt, override with -d <dir>
parentDirectory=/opt
installDirectoryName=GsDevKit

# How much feedback to provide
export verbose_level=0

while getopts ":p:n:v" o; do
  case $o in
    (p) parentDirectory=$OPTARG;;
    (n) installDirectoryName=$OPTARG;;
    (v) verbose_level=$((verbose_level + 1));;
    (*) usage
  esac
done

# Setup the environment
info "parentDirectory=$parentDirectory" 2
info "installDirectoryName=$installDirectoryName" 2
installPath="$parentDirectory/$installDirectoryName"
info "installPath=$installPath" 2
stonesGitRoot="$installPath/git"
info "stonesGitRoot=$stonesGitRoot" 2
stonesGitInstall=$stonesGitRoot/GsDevKit_stones
info "stonesGitInstall=$stonesGitInstall" 2
stonesHome=$installPath
info "stonesHome=$stonesHome" 2
stonesDataHome=$installPath/data
info "stonesDataHome=$stonesDataHome" 2
superDoitRoot=$stonesGitRoot/superDoit
info "superDoitRoot=$superDoitRoot" 2

# Ensure the shell session has the appropriate environment variables set
if [ "${STONES_HOME}x" = "x" ] ; then
	# Have the user update their profile
	info "Add the following to your shell profile typically ~/.zprofile (Mac 14.3), ~/.profile and/or ~/.bash_profile (Ubuntu & Mac 14.2 and earlier) then close and reopen this terminal" 0
	echo "# GsDevKit_stones
export STONES_HOME=$stonesHome
export STONES_DATA_HOME=\$STONES_HOME/data
export PATH=\$STONES_HOME/git/superDoit/bin:\$STONES_HOME/git/GsDevKit_stones/bin:\$PATH"

	exit_1_banner "STONES_HOME environment variable needs to be defined (see above message)"
fi

# Ensure git credentials have been setup
information_banner "Testing ssh connection to github.com"
if [[ $(ssh -T git@github.com 2>&1 | grep success | wc -c) -eq 0 ]]; then
	exit_1_banner "Setup your git credentials before re-running this script"
else
	information_banner "Success..."
fi

# Let's get the sudo password thing out of the way
information_banner "Enter your sudo password (may not be required if already entered recently)"
sudo date

# Get the logged in user name
#loggedInUser=$( echo "show State:/Users/ConsoleUser" | scutil | awk '/Name :/ && ! /loginwindow/ { print $3 }' )
loggedInUser=$USER
info "user=$loggedInUser" 2

# Setup GemStone directories
if [ ! -d "/opt/gemstone" ]; then
	info "Creating GemStone directories in /opt/gemstone" 1
	sudo mkdir -p /opt/gemstone
	sudo chmod oug+rwx /opt/gemstone
	sudo mkdir /opt/gemstone/locks
	sudo chmod oug+rwx /opt/gemstone/locks
else
	info "GemStone directories already exist in /opt/gemstone. If you want to recreate GemStone directories, delete them and re-run this script" 1
fi

# Make sure the install root path exists and is owned and accessible by the logged in user.
if [ ! -d "$parentDirectory" ]; then
	info "Creating $parentDirectory" 1
	sudo mkdir -p "$parentDirectory"
else
	info "$parentDirectory already exists. If you want to recreate $parentDirectory delete it and re-run this script." 1
fi
info "Setting owner of $parentDirectory to $loggedInUser" 2
sudo chown $loggedInUser "$parentDirectory"
info "Setting permissions of $parentDirectory to rwx" 2
chmod u+rwx "$parentDirectory"

# Make sure the install path exists.
conditionallyCreateDirectory "$installPath"
conditionallyCreateDirectory "$installPath/data"
conditionallyCreateDirectory "$installPath/gemstone"

# Make sure the git root exists.
conditionallyCreateDirectory "$stonesGitRoot"

# Install GsDevKit_stones
cd "$stonesGitRoot"
info "Cloning GsDevKit_stones in $stonesGitInstall" 1
git clone git@github.com:GsDevKit/GsDevKit_stones.git
cd "$stonesGitInstall"
#info "Switching to cf28c96b7 of GsDevKit_stones" 2
#git checkout cf28c96b7
info "Switching to cf28c96b7 of GsDevKit_stones" 2
git checkout v2.1
cd "$stonesGitInstall/bin"
info "Installing GsDevKit_stones and superDoit" 1
./install.sh

# Switch to superDoit v4.2
info "Switching to v4.2 of superDoit" 2
cd "$superDoitRoot"
git checkout v4.2

# Configure Shared Memory
info "Configure Shared Memory" 2
$superDoitRoot/dev/setSharedMemory.sh

# Return to the workingDirectory
cd $workingDirectory

# Setup BVC
#./installBVC.sh
./installGT4Gemstone.sh



exit_0_banner "...finished"
