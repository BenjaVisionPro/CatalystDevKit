#! /usr/bin/env sh
PROGNAME=$0
. private/shFeedback
start_banner

registryName=bvc_rowan
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
updateClientLibs.solo --registry=$registryName $gemstoneVersion

information_banner "Registering GemStone $gemstoneVersion"
registerProduct.solo --registry=$registryName --fromDirectory=$STONES_HOME/gemstone

information_banner "Creating Project Sets"
createProjectSet.solo --registry=$registryName --projectSet=rowanV3_common \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/rowanV3_common.ston
createProjectSet.solo --registry=$registryName --projectSet=rowanV3_gs \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/rowanV3_gs.ston
createProjectSet.solo --registry=$registryName --projectSet=rowanV3_pharo \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/rowanV3_pharo.ston
createProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--from=$STONES_HOME/git/GsDevKit_stones/projectSets/ssh/gt4gemstone.ston


information_banner "Creating Project Directory $STONES_HOME/$registryName"
projectPath=$STONES_HOME/$registryName
mkdir $projectPath
mkdir $projectPath/git

information_banner "Registering Project Git Directory $STONES_HOME/$registryName/git"
registerProjectDirectory.solo --registry=$registryName --projectDirectory=$projectPath/git

information_banner "Cloning Projects"
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=rowanV3_common \
	--projectDirectory=$projectPath/git/common_projects
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=rowanV3_gs \
	--projectDirectory=$projectPath/git/gs_projects
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=rowanV3_pharo \
	--projectDirectory=$projectPath/git/pharo_projects
cloneProjectsFromProjectSet.solo --registry=$registryName --projectSet=gt4gemstone \
	--projectDirectory=$projectPath/git/gt4gemstone

information_banner "Creating Project Stones Directory $STONES_HOME/$registryName/stones"
mkdir $projectPath/stones
registerStonesDirectory.solo --registry=$registryName \
                             --stonesDirectory=$projectPath/stones

information_banner "Creating Stone $stoneName"
createStone.solo --registry=$registryName --template=minimal_rowan $stoneName $gemstoneVersion

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

information_banner "Installing ROWAN in stone $stoneName"
cd $projectPath/stones/$stoneName





# turn on unicodeComparisonMode required by Jadeite
enableUnicodeCompares.topaz -lq
information_banner "installing GsCommands"
installProject.stone file:product/examples/GsCommands/projectsHome/GsCommands/rowan/specs/GsCommands.ston \
	--projectsHome=product/examples/GsCommands/projectsHome $*

information_banner "installing Announcements -- hack until we fix up reguired projects in RowanClientServices"
installProject.stone file:$projectPath/git/common_projects/Announcements/rowan/specs/Announcements.ston  \
	--projectsHome=$projectPath/git/common_projects $*

information_banner "installing RemoteServiceReplication -- partial workaround for https://github.com/GemTalk/Rowan/issues/905"
installProject.stone file:$projectPath/git/common_projects/RemoteServiceReplication/rowan/specs/RemoteServiceReplication.ston  \
	--projectsHome=$projectPath/git/common_projects $*

information_banner "installing RowanClientServices"
installProject.stone file:$projectPath/git/gs_projects/RowanClientServices/rowan/specs/RowanClientServices.ston  \
	--projectsHome=$projectPath/git/gs_projects
	
# attach stone to the Rowan projects that are part of the base image
attachRowanDevClones.stone --projectsHome=$projectPath/git/gs_projects $*

# install GsDevKit_stones using Rowan installProject.stone script
information_banner "installing GsDevKit_stones"
installProject.stone file:$STONES_HOME/git/GsDevKit_stones/rowan/specs/GsDevKit_stones.ston \
	--projectsHome=$STONES_HOME/git/GsDevKit_stones/.. $*

# install gt4gemstone
information_banner "installing gt4GemStone"
installProject.stone file:$projectPath/git/gt4gemstone/rowan/specs/gt4gemstone.ston  \
	--projectsHome=$projectPath/git/gt4gemstone




# Restore working directory
cd $workingDirectory
