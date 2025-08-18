#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

# User default registry ie. hostname
registryName=`/bin/hostname`

stoneName=gt
gemstoneVersion="3.7.4.3"

# Save current directory
workingDirectory=`PWD`
projectSetDirectory=$workingDirectory/../projectSets

# Setup the BenjaVision Catalyst development environment
information_banner "Version Report"
versionReport.solo

information_banner "Creating Registry $registryName"
createRegistry.solo $registryName

information_banner "Register Shared Product Directory $STONES_HOME/gemstone"
registerProductDirectory.solo --registry=$registryName --productDirectory=$STONES_HOME/gemstone

information_banner "Installing GemStone $gemstoneVersion"
downloadGemStone.solo --registry=$registryName $gemstoneVersion
updateClientLibs.solo --registry=$registryName $gemstoneVersion

information_banner "Registering GemStone $gemstoneVersion"
registerProduct.solo --registry=$registryName --fromDirectory=$STONES_HOME/gemstone

information_banner "Creating GT Project Set from $projectSetDirectory/gt4gemstone.ston"
createProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--from=$projectSetDirectory/gt4gemstone.ston

information_banner "Creating Project Directory $STONES_HOME/$registryName"
projectPath=$STONES_HOME/$registryName
mkdir $projectPath
mkdir $projectPath/git

information_banner "Registering Project Git Directory $STONES_HOME/$registryName/git"
registerProjectDirectory.solo --registry=$registryName --projectDirectory=$projectPath/git

information_banner "Cloning Projects"
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--projectDirectory=$projectPath/git

information_banner "Creating Project Stones Directory $STONES_HOME/$registryName/stones"
mkdir $projectPath/stones
registerStonesDirectory.solo --registry=$registryName \
                             --stonesDirectory=$projectPath/stones

information_banner "Creating Stone $stoneName"
createStone.solo --registry=$registryName --template=default_rowan3 $stoneName $gemstoneVersion

if [[ "$OSTYPE" == "darwin"* ]]; then
	# possible native code generation issues on mac and github, disable native code
	warning_banner "Disabling Native Code for stone $stoneName"
	cat - >> $STONES_HOME/$registryName/stones/$stoneName/gem.conf << EOF
GEM_NATIVE_CODE_ENABLED=0;
EOF
	cat $STONES_HOME/$registryName/stones/$stoneName/gem.conf
fi

information_banner "Setting ROWAN_PROJECTS_HOME"
export ROWAN_PROJECTS_HOME=$projectPath/git
updateCustomEnv.solo --registry=$registryName $stoneName --addKey=ROWAN_PROJECTS_HOME --value=$ROWAN_PROJECTS_HOME --restart

information_banner "Starting Stone $stoneName"
startStone.solo --registry=$registryName $stoneName -b
gslist.solo -l

information_banner "Installing in stone $stoneName"
cd $projectPath/stones/$stoneName



# turn on unicodeComparisonMode required by Jadeite
enableUnicodeCompares.topaz -lq

# install RSR
information_banner "installing RSR"
installProject.stone file:$projectPath/git/RemoteServiceReplication/rowan/specs/RemoteServiceReplication.ston  \
	--projectsHome=$projectPath/git -D

# install gtoolkit-wireencoding
information_banner "installing gtoolkit-wireencoding"
installProject.stone file:$projectPath/git/gtoolkit-wireencoding/rowan/specs/gtoolkit-wireencoding.ston  \
	--projectsHome=$projectPath/git -D

# install gtoolkit-remote
information_banner "installing gtoolkit-remote"
installProject.stone file:$projectPath/git/gtoolkit-remote/rowan/specs/gtoolkit-remote.ston  \
	--projectsHome=$projectPath/git -D

# install gt4gemstone
information_banner "installing gt4GemStone"
installProject.stone file:$projectPath/git/gt4gemstone/rowan/specs/gt4gemstone.ston  \
	--projectsHome=$projectPath/git -D



# Restore working directory
cd $workingDirectory
