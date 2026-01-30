Extension { #name : 'CRRuntimeRegistry' }

{ #category : '*bv-catalyst-runtime-ui' }
CRRuntimeRegistry >> gtRuntimesFor: aView [
	<gtView>
	^ aView columnedList
		title: 'Runtimes';
		priority: 10;
		items: [ self runtimes asArray ];
		column: 'Name' text: [ :each | each displayName ];
		column: 'Status' text: [ :each | each status asString ];
		column: 'Runners' text: [ :each | each runners size asString ]
]
