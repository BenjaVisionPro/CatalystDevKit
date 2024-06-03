"Load projects"
Metacello new
 baseline:'Seaside3';
 repository: 'github://SeasideSt/Seaside:master/repository';
 load: #('CI' 'Zinc' 'Development' 'JQuery').

"Metacello new
	repository: 'gitlocal:///opt/git/JupiterJones/Falcon4Seaside/src';
	baseline: 'Falcon4Seaside';
	load."
	
Metacello new
	repository: 'gitlocal:///opt/git/BenjaVision/CatalystDevKit/src';
	baseline: 'CatalystDevKit';
	load.

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

Metacello new
	repository: 'gitlocal:///Users/jupiter/Documents/Projects/Boundless/src';
	baseline: 'Boundless';
	load.
	
Metacello new
	repository: 'gitlocal:///opt/git/JupiterSmalltalk/echarts4seaside/src';
	baseline: 'ECharts';
	load.


"Open BVC Dev kit World"
5 seconds wait.
(Smalltalk at: #BVCDevKit) initializeKnowledgeBase.
5 seconds wait.
(Smalltalk at: #BVCDevKitWorld) openDefault.
5 seconds wait.
(Smalltalk at: #GtWorld) allInstances first close.