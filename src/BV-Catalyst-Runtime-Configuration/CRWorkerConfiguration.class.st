Class {
	#name : 'CRWorkerConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'displayName',
		'workerClassName',
		'schedulerConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRWorkerConfiguration >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CRWorkerConfiguration >> displayName: aString [
	displayName := aString asString
]

{ #category : 'accessing' }
CRWorkerConfiguration >> identifier [
	^ identifier
]

{ #category : 'accessing' }
CRWorkerConfiguration >> identifier: aSymbol [
	identifier := aSymbol
]

{ #category : 'initialization' }
CRWorkerConfiguration >> initialize [
	super initialize.
	displayName := ''.
	identifier := ''.
	workerClassName := ''.
	schedulerConfiguration := nil
]

{ #category : 'accessing' }
CRWorkerConfiguration >> schedulerConfiguration [
	^ schedulerConfiguration
]

{ #category : 'accessing' }
CRWorkerConfiguration >> schedulerConfiguration: aCRWorkSchedulerConfiguration [
	schedulerConfiguration := aCRWorkSchedulerConfiguration
]

{ #category : 'validation' }
CRWorkerConfiguration >> validateOn: result [
	| workerLabel |
	workerLabel := identifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ identifier printString ].

	identifier isNil
		ifTrue: [ result addError: 'Worker identifier is required.' ]
		ifFalse: [ identifier isSymbol
				ifFalse: [ result
						addError: 'Worker identifier must be a Symbol; got ' , identifier printString , ' ('
								, identifier class name , ').' ] ].

	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Worker ' , workerLabel , ' displayName is required.' ].

	(workerClassName isNil or: [ workerClassName asString isEmpty ])
		ifTrue: [ result addError: 'Worker ' , workerLabel , ' workerClassName is required.' ].

	schedulerConfiguration
		ifNotNil: [ schedulerConfiguration
				validateOn: result
				forWorkerIdentifier: (identifier isSymbol ifTrue: [ identifier ] ifFalse: [ nil ]) ]
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClassName [
	^ workerClassName
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClassName: aString [
	workerClassName := aString asString
]
