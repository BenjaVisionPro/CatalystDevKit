#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

# install location
installLocation=$(PWD)/gt

information_banner "Creating Install Location: ${installLocation}"
# create install location
mkdir -p $installLocation

# download platform specific GT
set_architecture
downloadFile=`curl -s -o /dev/stdout https://dl.feenk.com/gt/GlamorousToolkit$(architecture)-release`
downloadLink=https://dl.feenk.com/gt/${downloadFile}

# download and unzip
downloadLink=https://dl.feenk.com/gt/${downloadFile}
information_banner "Downloading from: ${downloadLink}"
curl -LO "${downloadLink:-}" \
&& unzip -qq -d "${installLocation}" "${downloadFile}" \
&& rm "${downloadFile}"

# install stuff in gt
information_banner "Configure GT for BenjaVision Catalyst DevKit"
spinner_start "Installing Projects... "
$installLocation/GlamorousToolkit.app/Contents/MacOS/GlamorousToolkit-cli $installLocation/GlamorousToolkit.image st "loadBVCDevKit.st" --interactive --save --quit
spinner_stop

information_banner "Setup complete"
exit 0