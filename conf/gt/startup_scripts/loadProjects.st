| localProjectsPath connector |

localProjectsPath := 'gitlocal://', FileSystem workingDirectory fullName, '/git'.

"Create a GemStone connector"
"
connector := GtGemStoneSessionRegistry default propertiesFile addNewConnector.
connector
	name: 'bvc_dev';
	host: 'localhost';
	libraryPath: '/opt/GsDevKit/gemstone/clientlibs' asFileReference;
	gemstoneVersion: '3.7.4.3';
	stone: 'bvc_dev';
	netldi: 'bvc_dev_ldi';
	username: 'SystemUser';
	password: 'swordfish';
	hostUsername: '$USER';
	hostPassword: '<password>'.
connector
	notifyNameChanged;
	notifyUpdated.
"

"Load projects"
"
Metacello new
	repository: 'github://svenvc/NeoCSV/repository';
	baseline: 'NeoCSV';
	load.

Metacello new
	repository: 'github://svenvc/NeoJSON/repository';
	baseline: 'NeoJSON';
	load.

Metacello new
	baseline:'Seaside3';
	repository: 'github://SeasideSt/Seaside:master/repository';
	load: #('CI' 'Zinc' 'Development' 'JQuery').

Metacello new
	baseline: 'Dynabook';
	repository: 'github://seandenigris/Dynabook';
	onConflictUseLoaded;
	load.

Metacello new
	baseline: 'RenoirSt';
	repository: 'github://ba-st/RenoirSt:release-candidate';
	onConflictUseLoaded;
	load: #('Development' 'Development-Seaside-Extensions').

Metacello new
	repository: 'gitlocal:///Users/jupiter/Documents/Projects/Boundless/src';
	baseline: 'Boundless';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/JupiterJones/Falcon4Seaside/src';
	baseline: 'Falcon4Seaside';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/JupiterSmalltalk/echarts4seaside/src';
	baseline: 'ECharts';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/JupiterJones/JupiterWeb/src';
	baseline: 'JupiterWeb';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/Benjability/BenjabilityWeb/src';
	baseline: 'BenjabilityWeb';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/fios-systems/FIOSWeb/src';
	baseline: 'FIOSWeb';
	load.

Metacello new
	repository: 'gitlocal:///opt/git/BenjaVision/CatalystWeb/src';
	baseline: 'CatalystWeb';
	load.
"
Transcript show: 'LOADING CatalystDevKit FROM PATH: ', localProjectsPath.
Metacello new
	repository: localProjectsPath, '/CatalystDevKit/src';
	baseline: 'CatalystDevKit';
	load.

2 seconds wait