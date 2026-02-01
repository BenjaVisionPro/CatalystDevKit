Class {
	#name : 'CRWorkerDeploymentConfiguration',
	#superclass : 'Object',
	#instVars : [
		'workerIdentifier',
		'initialCount',
		'scalingConfiguration'
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
	scalingConfiguration := nil
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> scalingConfiguration [
	^ scalingConfiguration
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> scalingConfiguration: aCRScalingConfiguration [
	scalingConfiguration := aCRScalingConfiguration
]

{ #category : 'validation' }
CRWorkerDeploymentConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers [
	workerIdentifier isEmpty ifTrue: [ aValidationResult addError: 'Deployment entry must specify workerIdentifier.' ].
	(knownWorkerIdentifiers includes: workerIdentifier) ifFalse: [ aValidationResult addError: 'Deployment references unknown workerIdentifier ', workerIdentifier printString, '.' ].
	(initialCount isInteger and: [ initialCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Deployment initialCount for ', workerIdentifier printString, ' must be >= 0.' ].
	scalingConfiguration ifNotNil: [ scalingConfiguration validateOn: aValidationResult forWorkerIdentifier: workerIdentifier ].
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier [
	^ workerIdentifier
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier: aString [
	workerIdentifier := aString asString
]
