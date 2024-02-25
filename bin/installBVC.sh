#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

registryName=bvc
stoneName=$registryName
gemstoneVersion="3.7.0"

# Save current directory
workingDirectory=`PWD`

# Setup the BenjaVision Catalyst development environment
information_banner "Version Report"
versionReport.solo

information_banner "Creating Registry $registryName"
createRegistry.solo $registryName

information_banner "Register Shared Product Directory $STONES_HOME/gemstone"
registerProductDirectory.solo --registry=$registryName --productDirectory=$STONES_HOME/gemstone

information_banner "Installing GemStone $gemstoneVersion"
downloadGemStone.solo --registry=$registryName $gemstoneVersion

information_banner "Registering GemStone $gemstoneVersion"
registerProduct.solo --registry=$registryName --fromDirectory=$STONES_HOME/gemstone

information_banner "Creating Project Sets"
createProjectSet.solo --registry=$registryName --projectSet=devkit \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/devkit.ston
createProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/gt4gemstone.ston

information_banner "Creating Project Directory $STONES_HOME/$registryName"
projectPath=$STONES_HOME/$registryName
mkdir $projectPath
mkdir $projectPath/git

information_banner "Registering Project Git Directory $STONES_HOME/$registryName/git"
registerProjectDirectory.solo --registry=$registryName --projectDirectory=$projectPath/git

information_banner "Cloning Projects"
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=devkit \
	--projectDirectory=$projectPath/git
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--projectDirectory=$projectPath/git

information_banner "Creating Project Stones Directory $STONES_HOME/$registryName/stones"
mkdir $projectPath/stones
registerStonesDirectory.solo --registry=$registryName \
                             --stonesDirectory=$projectPath/stones

information_banner "Register Shared tODE Directory"
todeHome=$STONES_HOME/tode
mkdir $todeHome
registerTodeSharedDir.solo --registry=$registryName \
                           --todeHome=$todeHome \
                           --populate

information_banner "Creating Stone $stoneName"
createStone.solo --registry=$registryName --template=default_tode $stoneName $gemstoneVersion

if [[ "$OSTYPE" == "darwin"* ]]; then
	# possible native code generation issues on mac and github, disable native code
	warning_banner "Disabling Native Code for stone $stoneName"
	cat - >> $STONES_HOME/$registryName/stones/$stoneName/gem.conf << EOF
GEM_NATIVE_CODE_ENABLED=0;
EOF
	cat $STONES_HOME/$registryName/stones/$stoneName/gem.conf
fi

information_banner "Starting Stone $stoneName"
startStone.solo --registry=$registryName $stoneName -b
gslist.solo -l

information_banner "Installing tODE in stone $stoneName"
cd $projectPath/stones/$stoneName
loadTode.stone --projectDirectory=$projectPath/git
todeIt.stone --file=$STONES_HOME/git/GsDevKit_stones/tode/setUpSys_1
validateStoneSysNodes.stone --todeHome=$todeHome --stoneName=$stoneName \
	--files --repair $*
todeIt.stone --file=$STONES_HOME/git/GsDevKit_stones/tode/setUpSys_2

# Restore working directory
cd $workingDirectory
