#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

# download platform specific GT
set_platform_and_architecture
downloadFile=$(curl -s https://dl.feenk.com/gt/GlamorousToolkit${architecture}-release 2> /dev/null)
downloadLink=https://dl.feenk.com/gt/${downloadFile}

# install location
information_banner "Creating Install Location: ${installLocation}"
installLocation=../IDE
mkdir -p $installLocation

# download and unzip
downloadLink=https://dl.feenk.com/gt/${downloadFile}
information_banner "Downloading from: ${downloadLink}"
#cp ../$downloadFile . \
curl -LO "${downloadLink:-}" \
&& unzip -qq -d "${installLocation}" "${downloadFile}" \
&& rm "${downloadFile}"

# install stuff in gt
information_banner "Configure GT for BenjaVision Catalyst DevKit"

if [ "${platform}" = "Mac" ]; then
	cli=GlamorousToolkit.app/Contents/MacOS/GlamorousToolkit-cli
	executable=GlamorousToolkit.app
	bvc=BVCDevKit.app
elif [  "${platform}" = "Linux" ]; then
	cli=bin/GlamorousToolkit-cli
	executable=bin/GlamorousToolkit
	bvc=bin/BVCDevKit
elif [  "${platform}" = "Win" ]; then
	cli=bin/GlamorousToolkit-cli
	executable=bin/GlamorousToolkit.exe
	bvc=bin/BVCDevKit.exe
fi

spinner_start "Installing Projects... "

$installLocation/$cli $installLocation/GlamorousToolkit.image st "st/preLoad.st"  --interactive --save --quit
rm "$installLocation/GlamorousToolkit.image" "$installLocation/GlamorousToolkit.changes"

$installLocation/$cli $installLocation/BVCDevKit.image st "st/loadProjects.st" --save --quit
$installLocation/$cli $installLocation/BVCDevKit.image st "st/postLoad.st"  --interactive --save --quit
mv "$installLocation/$executable" "$installLocation/$bvc"

if [ "${platform}" = "Win" ]; then
	ln -s "$installLocation/$bvc" "$installLocation/BVCDevKit.exe"
fi

spinner_stop

information_banner "Setup complete"
exit 0