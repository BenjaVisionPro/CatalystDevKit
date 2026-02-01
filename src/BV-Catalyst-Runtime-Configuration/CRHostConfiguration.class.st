Class {
	#name : 'CRHostConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'displayName',
		'address',
		'maxProcesses',
		'workers'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRHostConfiguration >> address [ ^ address
]

{ #category : 'accessing' }
CRHostConfiguration >> address: aString [
	address := aString
]

{ #category : 'accessing' }
CRHostConfiguration >> displayName [ ^ displayName
]

{ #category : 'accessing' }
CRHostConfiguration >> displayName: aString [
	displayName := aString
]

{ #category : 'accessing' }
CRHostConfiguration >> identifier [ ^ identifier
]

{ #category : 'accessing' }
CRHostConfiguration >> identifier: aSymbol [
	identifier := aSymbol
]

{ #category : 'initialization' }
CRHostConfiguration >> initialize [
	super initialize.
	identifier := ''.
	displayName := ''.
	address := ''.
	maxProcesses := 0.
	workers := OrderedCollection new
]

{ #category : 'accessing' }
CRHostConfiguration >> maxProcesses [ ^ maxProcesses
]

{ #category : 'accessing' }
CRHostConfiguration >> maxProcesses: anInteger [ maxProcesses := anInteger asInteger
]

{ #category : 'validation' }
CRHostConfiguration >> validateOn: result knownWorkerIdentifiers: knownWorkerIds [
	identifier isSymbol
		ifFalse: [ result addError: 'Host identifier must be a Symbol' ].

	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Host displayName is required.' ].

	(address isNil or: [ address asString isEmpty ])
		ifTrue: [ result addError: 'Host address is required.' ].

	(maxProcesses isInteger and: [ maxProcesses >= 0 ])
		ifFalse: [ result addError: 'Host maxProcesses must be a non-negative Integer.' ].

	workers
		ifNil: [ result addError: 'Host workers is required.'.
			^ self ].

	(workers allSatisfy: [ :each | each isSymbol ])
		ifFalse: [ result addError: 'Host workers must be Symbols' ].	"Only do reference checks if types are correct"
	(workers allSatisfy: [ :each | each isSymbol ])
		ifTrue: [ workers
				do: [ :each | 
					(knownWorkerIds includes: each)
						ifFalse: [ result addError: 'Host references unknown worker ' , each printString , '.' ] ] ]
]

{ #category : 'accessing' }
CRHostConfiguration >> workers [ ^ workers
]

{ #category : 'accessing' }
CRHostConfiguration >> workers: aCollection [ workers := aCollection asOrderedCollection
]
