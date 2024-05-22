"Close world"
(Smalltalk at: #GtWorld) allInstances first close.

"Load projects"
"Metacello new
 baseline:'Seaside3';
 repository: 'github://SeasideSt/Seaside:master/repository';
 load: #('CI' 'Zinc' 'Development' 'JQuery').

Metacello new
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

"Open BVC Dev kit World"
(Smalltalk at: #BVCDevKitWorld) initializeKnowledgeBase.
10 seconds wait.
(Smalltalk at: #BVCDevKitWorld) openDefault