| projectsRoot connector |

projectsRoot := 'gitlocal://', (OSPlatform current environment at: 'PROJECTS_ROOT').

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
Transcript show: 'LOADING CatalystDevKit FROM ', 
	(projectsRoot ifNil: ['<none>']).
	
Metacello new
	repository: projectsRoot, '/CatalystDevKit/src';
	baseline: 'CatalystDevKit';
	load.

2 seconds wait