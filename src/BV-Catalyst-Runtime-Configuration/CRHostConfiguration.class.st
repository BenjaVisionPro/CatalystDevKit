Class {
	#name : 'CRHostConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'displayName',
		'address',
		'maxProcesses',
		'workers',
		'tags',
		'services'
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

{ #category : 'accessing' }
CRHostConfiguration >> services [
	^ services
]

{ #category : 'accessing' }
CRHostConfiguration >> services: anObject [
	services := anObject
]

{ #category : 'accessing' }
CRHostConfiguration >> tags [
	^ tags
]

{ #category : 'accessing' }
CRHostConfiguration >> tags: anObject [
	tags := anObject
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

{ #category : 'validation' }
CRHostConfiguration >> validateOn: result knownWorkerIdentifiers: knownWorkerIds knownServiceIdentifiers: knownServiceIds [
	| hostLabel |
	hostLabel := identifier ifNil: [ '<nil>' ] ifNotNil: [ identifier printString ].

	identifier isNil
		ifTrue: [ result addError: 'Host identifier is required.' ]
		ifFalse: [ identifier isSymbol
				ifFalse: [ result
						addError: 'Host identifier must be a Symbol; got ' , identifier printString , ' ('
								, identifier class name , ').' ] ].

	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Host ' , hostLabel , ' displayName is required.' ].

	(address isNil or: [ address asString isEmpty ])
		ifTrue: [ result addError: 'Host ' , hostLabel , ' address is required.' ].

	(maxProcesses isInteger and: [ maxProcesses >= 0 ])
		ifFalse: [ result
				addError: 'Host ' , hostLabel , ' maxProcesses must be a non-negative Integer; got '
						, maxProcesses printString , '.' ].

	(tags isNil or: [ tags isCollection not ])
		ifTrue: [ result
				addError: 'Host ' , hostLabel , ' tags must be a collection of Symbols.' ]
		ifFalse: [ (tags allSatisfy: [ :each | each isSymbol ])
				ifFalse: [ result
						addError: 'Host ' , hostLabel , ' tags must be Symbols; got ' , tags printString , '.' ] ].

	(workers isNil or: [ workers isCollection not ])
		ifTrue: [ result
				addError: 'Host ' , hostLabel , ' workers must be a collection of Symbols.' ]
		ifFalse: [ (workers allSatisfy: [ :each | each isSymbol ])
				ifFalse: [ result
						addError: 'Host ' , hostLabel , ' workers must be Symbols; got ' , workers printString
								, '.' ]
				ifTrue: [ workers
						do: [ :each | 
							(knownWorkerIds includes: each)
								ifFalse: [ result
										addError: 'Host ' , hostLabel , ' references unknown worker ' , each printString , '.' ] ] ] ].

	(services isNil or: [ services isCollection not ])
		ifTrue: [ result
				addError: 'Host ' , hostLabel , ' services must be a collection of Symbols.' ]
		ifFalse: [ (services allSatisfy: [ :each | each isSymbol ])
				ifFalse: [ result
						addError: 'Host ' , hostLabel , ' services must be Symbols; got ' , services printString
								, '.' ]
				ifTrue: [ services
						do: [ :each | 
							(knownServiceIds includes: each)
								ifFalse: [ result
										addError: 'Host ' , hostLabel , ' references unknown service ' , each printString , '.' ] ] ] ].

	(workers isEmpty and: [ services isEmpty ])
		ifTrue: [ result
				addError: 'Host ' , hostLabel , ' allows no workers and no services. Add at least one.' ]
]

{ #category : 'accessing' }
CRHostConfiguration >> workers [ ^ workers
]

{ #category : 'accessing' }
CRHostConfiguration >> workers: aCollection [ workers := aCollection asOrderedCollection
]
