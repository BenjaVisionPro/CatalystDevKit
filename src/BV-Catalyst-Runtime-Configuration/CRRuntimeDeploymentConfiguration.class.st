Class {
	#name : 'CRRuntimeDeploymentConfiguration',
	#superclass : 'Object',
	#instVars : [
		'serviceDeployments'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRRuntimeDeploymentConfiguration >> initialize [
	super initialize.
	serviceDeployments := OrderedCollection new
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> serviceDeployments [
	^ serviceDeployments
]

{ #category : 'accessing' }
CRRuntimeDeploymentConfiguration >> serviceDeployments: anObject [
	serviceDeployments := anObject
]

{ #category : 'validation' }
CRRuntimeDeploymentConfiguration >> validateOn: aValidationResult knownServiceIdentifiers: knownServiceIds [
	serviceDeployments ifNil: [ ^ self ].

	(serviceDeployments collect: #serviceIdentifier) asSet size
		= serviceDeployments size
		ifFalse: [ aValidationResult addError: 'Duplicate deployment serviceIdentifier.' ].

	serviceDeployments
		do: [ :each | each validateOn: aValidationResult knownServiceIdentifiers: knownServiceIds ]
]
