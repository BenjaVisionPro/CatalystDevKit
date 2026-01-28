Extension { #name : 'CRRuntimeRegistry' }

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntimeRegistry >> gtRuntimesFor: aView [
	"I show the registered runtimes so I can find and stop them."

	<gtView>
	^ aView columnedList
		title: 'Runtimes';
		priority: 10;
		items: [ self runtimes asArray ];
		column: 'Name' text: [ :each | each displayName ];
		column: 'Running' text: [ :each | each isRunning asString ];
		column: 'Runners' text: [ :each | each runners size asString ]
]
