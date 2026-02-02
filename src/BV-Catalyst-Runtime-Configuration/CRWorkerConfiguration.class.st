Class {
	#name : 'CRWorkerConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'displayName',
		'schedulerConfiguration',
		'workerClass',
		'services'
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
	displayName := aString
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
	workerClass := ''.
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

{ #category : 'accessing' }
CRWorkerConfiguration >> services [
	^ services
]

{ #category : 'accessing' }
CRWorkerConfiguration >> services: anObject [
	services := anObject
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

	workerClass isNil
		ifTrue: [ result addError: 'Worker ' , workerLabel , ' workerClass is required.' ]
		ifFalse: [ workerClass isSymbol
				ifFalse: [ result
						addError: 'Worker ' , workerLabel , ' workerClass must be a Symbol; got '
								, workerClass printString , ' (' , workerClass class name , ').' ] ].

	schedulerConfiguration
		ifNotNil: [ schedulerConfiguration
				validateOn: result
				forWorkerIdentifier: (identifier isSymbol ifTrue: [ identifier ] ifFalse: [ nil ]) ]
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClass [
	^ workerClass
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClass: aSymbol [
	workerClass := aSymbol
]
