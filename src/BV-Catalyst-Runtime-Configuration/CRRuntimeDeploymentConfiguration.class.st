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

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeployments [
	^ workerDeployments
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeployments: aCollection [
	workerDeployments := aCollection asOrderedCollection
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> workerDeploymentForIdentifier: aWorkerIdentifier [
	^ workerDeployments
		detect: [ :each | each workerIdentifier = aWorkerIdentifier asString ]
		ifNone: [ nil ]
]

{ #category : 'validation' }
CRRuntimeDeploymentConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers [
	| ids |
	ids := Set new.
	workerDeployments do: [ :each |
		each validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers.
		(each workerIdentifier isEmpty) ifFalse: [
			(ids includes: each workerIdentifier)
				ifTrue: [ aValidationResult addError: 'Duplicate deployment entry for worker ', each workerIdentifier printString, '.' ]
				ifFalse: [ ids add: each workerIdentifier ] ] ].
]
