Extension { #name : 'CRRuntime' }

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntime >> gtOverviewFor: aView [
	"I show the current state of the runtime in a stable, non-flashy way."

	<gtView>
	^ aView textEditor
		title: 'Overview';
		priority: 10;
		text: [ String
				streamContents: [ :s | 
					s
						nextPutAll: (displayName ifNil: [ 'Catalyst Runtime' ]);
						cr;
						cr;
						nextPutAll: 'Running: ';
						nextPutAll: isRunning asString;
						cr;
						nextPutAll: 'Runners: ';
						nextPutAll: runners size asString;
						cr ] ]
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
