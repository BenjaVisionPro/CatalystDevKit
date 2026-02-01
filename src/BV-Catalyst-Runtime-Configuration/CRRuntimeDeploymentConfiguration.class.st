Class {
	#name : 'CRRuntimeDeploymentConfiguration',
	#superclass : 'Object',
	#instVars : [
		'workerDeployments'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRRuntimeDeploymentConfiguration >> initialize [
	super initialize.
	workerDeployments := OrderedCollection new
]

{ #category : 'validation' }
CRRuntimeDeploymentConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIds [
	workerDeployments ifNil: [ ^ self ].	"Uniqueness"
	(workerDeployments collect: #workerIdentifier) asSet size
		= workerDeployments size
		ifFalse: [ aValidationResult addError: 'Duplicate deployment workerIdentifier' ].

	workerDeployments
		do: [ :each | each validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIds ]
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeploymentForIdentifier: aWorkerIdentifier [
	^ workerDeployments
		detect: [ :each | each workerIdentifier = aWorkerIdentifier asString ]
		ifNone: [ nil ]
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeployments [
	^ workerDeployments
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeployments: aCollection [
	workerDeployments := aCollection asOrderedCollection
]
