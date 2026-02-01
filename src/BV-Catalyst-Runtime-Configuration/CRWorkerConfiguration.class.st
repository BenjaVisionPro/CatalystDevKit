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
CRWorkerConfiguration >> identifier: aString [
	identifier := aString asString
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
CRWorkerConfiguration >> validateOn: aValidationResult [
	identifier isEmpty ifTrue: [ aValidationResult addError: 'Worker identifier is required.' ].
	workerClassName isEmpty ifTrue: [ aValidationResult addError: 'Worker class name is required for ', identifier printString, '.' ].
	schedulerConfiguration ifNotNil: [ schedulerConfiguration validateOn: aValidationResult forWorkerIdentifier: identifier ].
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClassName [
	^ workerClassName
]

{ #category : 'accessing' }
CRWorkerConfiguration >> workerClassName: aString [
	workerClassName := aString asString
]
