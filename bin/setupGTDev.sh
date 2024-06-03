#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

# download platform specific GT
set_platform_and_architecture
downloadFile=`curl -s -o /dev/stdout https://dl.feenk.com/gt/GlamorousToolkit${architecture}-release`
downloadLink=https://dl.feenk.com/gt/${downloadFile}

# install location
information_banner "Creating Install Location: ${installLocation}"
installLocation=$(PWD)/gt
mkdir -p $installLocation

# download and unzip
downloadLink=https://dl.feenk.com/gt/${downloadFile}
information_banner "Downloading from: ${downloadLink}"
curl -LO "${downloadLink:-}" \
&& unzip -qq -d "${installLocation}" "${downloadFile}" \
&& rm "${downloadFile}"

# install stuff in gt
information_banner "Configure GT for BenjaVision Catalyst DevKit"

if [ "${platform}" = "Mac" ]; then
	executable=GlamorousToolkit.app/Contents/MacOS/GlamorousToolkit-cli
elif [  "${platform}" = "Linux" ]; then
	GlamorousToolkit-cli
elif [  "${platform}" = "Win" ]; then
	GlamorousToolkit.exe
fi

spinner_start "Installing Projects... "

$installLocation/$executable $installLocation/GlamorousToolkit.image st "st/loadProjects.st"  --save --quit
$installLocation/$executable $installLocation/GlamorousToolkit.image st "st/postLoad.st"   --interactive --save --quit

spinner_stop

information_banner "Setup complete"
exit 0