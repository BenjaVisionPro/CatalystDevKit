Extension { #name : 'CRRuntime' }

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtActionStartOn: anAction [
	"I start the runtime."

	<gtAction>
	^ anAction button
		icon: BrGlamorousVectorIcons play;
		tooltip: 'Start the Runtime';
		menuDisable: [ isRunning ];
		action: [ self start ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtActionStopOn: anAction [
	"I stop the runtime."

	<gtAction>
	^ anAction button
		icon: BrGlamorousVectorIcons stop;
		tooltip: 'Stop the Runtime';
		menuDisable: [ isRunning not ];
		action: [ self stop ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtRunnersFor: aView [
	"I show the runtime’s runners so I can drill into them."

	<gtView>
	^ aView columnedList
		title: 'Runners';
		priority: 20;
		items: [ runners values asArray ];
		column: 'Runner' text: [ :each | each gtDisplayText ];
		column: 'Running' text: [ :each | each isRunning asString ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtViewOverviewOn: aView [
	"I show the current runtime state (no telemetry yet)."

	<gtView>
	^ aView columnedList
		title: 'Overview';
		priority: 10;
		items: [ {#displayName -> (displayName ifNil: [ 'Catalyst Runtime' ]).
				#isRunning -> isRunning.
				#workerCount -> (workers ifNil: [ #() ]) size.
				#runnerCount -> (runners ifNil: [ IdentityDictionary new ]) size} ];
		column: 'Key' text: [ :assoc | assoc key asString ];
		column: 'Value' text: [ :assoc | assoc value asString ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtViewWorkersOn: aView [
	"I show my registered workers (the intent-level objects)."

	<gtView>
	^ aView list
		title: 'Workers';
		priority: 20;
		items: [ workers ifNil: [ #() ] ]
]
