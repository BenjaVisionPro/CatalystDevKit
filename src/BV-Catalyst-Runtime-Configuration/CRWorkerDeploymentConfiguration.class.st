Class {
	#name : 'CRWorkerDeploymentConfiguration',
	#superclass : 'Object',
	#instVars : [
		'workerIdentifier',
		'initialCount',
		'scaleConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> initialCount [
	^ initialCount
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> initialCount: anInteger [
	initialCount := anInteger asInteger
]

{ #category : 'initialization' }
CRWorkerDeploymentConfiguration >> initialize [
	super initialize.
	workerIdentifier := ''.
	initialCount := 0.
	scaleConfiguration := nil
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> scaleConfiguration [
	^ scaleConfiguration
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> scaleConfiguration: aCRScaleConfiguration [
	scaleConfiguration := aCRScaleConfiguration
]

{ #category : 'validation' }
CRWorkerDeploymentConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers [
	workerIdentifier isEmpty ifTrue: [ aValidationResult addError: 'Deployment entry must specify workerIdentifier.' ].
	(knownWorkerIdentifiers includes: workerIdentifier) ifFalse: [ aValidationResult addError: 'Deployment references unknown workerIdentifier ', workerIdentifier printString, '.' ].
	(initialCount isInteger and: [ initialCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Deployment initialCount for ', workerIdentifier printString, ' must be >= 0.' ].
	scaleConfiguration ifNotNil: [ scaleConfiguration validateOn: aValidationResult forWorkerIdentifier: workerIdentifier ].
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier [
	^ workerIdentifier
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier: aSymbol [
	workerIdentifier := aSymbol
]
