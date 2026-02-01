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
CRHostConfiguration >> address: aString [ address := aString asString
]

{ #category : 'accessing' }
CRHostConfiguration >> displayName [ ^ displayName
]

{ #category : 'accessing' }
CRHostConfiguration >> displayName: aString [ displayName := aString asString
]

{ #category : 'accessing' }
CRHostConfiguration >> identifier [ ^ identifier
]

{ #category : 'accessing' }
CRHostConfiguration >> identifier: aString [ identifier := aString asString
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
CRHostConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers [
	identifier isEmpty ifTrue: [ aValidationResult addError: 'Host identifier is required.' ].
	address isEmpty ifTrue: [ aValidationResult addWarning: 'Host ', identifier printString, ' has empty address.' ].
	(maxProcesses isInteger and: [ maxProcesses >= 0 ]) ifFalse: [ aValidationResult addError: 'Host ', identifier printString, ' maxProcesses must be >= 0.' ].
	workers do: [ :workerId |
		(knownWorkerIdentifiers includes: workerId asString)
			ifFalse: [ aValidationResult addError: 'Host ', identifier printString, ' references unknown worker ', workerId printString, '.' ] ].
]

{ #category : 'accessing' }
CRHostConfiguration >> workers [ ^ workers
]

{ #category : 'accessing' }
CRHostConfiguration >> workers: aCollection [ workers := aCollection asOrderedCollection
]
