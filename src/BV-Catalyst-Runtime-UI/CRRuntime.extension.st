Extension { #name : 'CRRuntime' }

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtActionStartOn: anAction [
	<gtAction>
	^ anAction button
		icon: BrGlamorousVectorIcons play;
		tooltip: 'Start the Runtime';
		menuDisable: [ self status == CRStatus running or: [ self status == CRStatus startingUp ] ];
		action: [ self start ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtActionStopOn: anAction [
	<gtAction>
	^ anAction button
		icon: BrGlamorousVectorIcons stop;
		tooltip: 'Stop the Runtime (graceful)';
		menuDisable: [ self status == CRStatus stopped or: [ self status == CRStatus shuttingDown ] ];
		action: [ self shutdownGraceful ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtRunnersFor: aView [
	<gtView>
	^ aView columnedList
		title: 'Runners';
		priority: 20;
		items: [ runners values asArray ];
		column: 'Runner' text: [ :each | each gtDisplayText ];
		column: 'Status' text: [ :each | each status asString ]
]

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtViewOverviewOn: aView [
	"I show the current runtime state (no telemetry yet)."

	<gtView>
	^ aView explicit
		title: 'Overview';
		priority: 1;
		stencil: [ (CRRuntimeOverviewWidget new
				runtime: self;
				yourself) margin: (BlInsets all: 2) ]
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
