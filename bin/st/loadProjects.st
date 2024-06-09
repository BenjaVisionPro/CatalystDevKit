| localRepoPath |

localRepoPath := 'gitlocal://',  (FileLocator image fullPath parentUpTo: 'CatalystDevKit') fullName, '/src'.

"Load projects"
Metacello new
	repository: 'github://feenkcom/gt4llm:main/src';
	baseline: 'Gt4Llm';
	load.

Metacello new
	repository: 'github://feenkcom/gt4llm:main/src';
	baseline: 'Gt4OpenAI';
	load.

Metacello new
   baseline: 'Futures';
   repository: 'github://feenkcom/pharo-futures:main/src';
   load.
"
Metacello new
 baseline:'Seaside3';
 repository: 'github://SeasideSt/Seaside:master/repository';
 load: #('CI' 'Zinc' 'Development' 'JQuery').

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
"

Metacello new
	repository: localRepoPath;
	baseline: 'CatalystDevKit';
	load.

10 seconds wait