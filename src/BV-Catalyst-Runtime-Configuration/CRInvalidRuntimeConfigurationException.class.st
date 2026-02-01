Class {
	#name : 'CRInvalidRuntimeConfigurationException',
	#superclass : 'Error',
	#instVars : [
		'validationResult',
		'configuration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'instance creation' }
CRInvalidRuntimeConfigurationException class >> configuration: aConfiguration validationResult: aValidationResult [
	^ self new
		configuration: aConfiguration;
		validationResult: aValidationResult;
		yourself
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> configuration [
	^ configuration
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> configuration: anObject [
	configuration := anObject
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> validationResult [
	^ validationResult
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> validationResult: aValidationResult [
	validationResult := aValidationResult
]
