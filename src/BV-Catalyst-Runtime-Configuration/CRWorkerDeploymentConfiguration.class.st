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
CRWorkerDeploymentConfiguration >> validateOn: result knownWorkerIdentifiers: knownIds [
	workerIdentifier isSymbol
		ifFalse: [ result addError: 'Deployment workerIdentifier must be a Symbol' ]
		ifTrue: [ (knownIds includes: workerIdentifier)
				ifFalse: [ result
						addError: 'Deployment workerIdentifier references unknown worker '
								, workerIdentifier printString , '.' ] ].

	(initialCount isInteger and: [ initialCount >= 0 ])
		ifFalse: [ result addError: 'Deployment initialCount must be a non-negative Integer.' ].

	(workerIdentifier isSymbol and: [ scaleConfiguration notNil ])
		ifTrue: [ scaleConfiguration validateOn: result forWorkerIdentifier: workerIdentifier ]
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier [
	^ workerIdentifier
]

{ #category : 'accessing' }
CRWorkerDeploymentConfiguration >> workerIdentifier: aSymbol [
	workerIdentifier := aSymbol
]
