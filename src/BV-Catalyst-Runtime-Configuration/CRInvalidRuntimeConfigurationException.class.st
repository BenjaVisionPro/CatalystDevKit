Class {
	#name : 'CRInvalidRuntimeConfigurationException',
	#superclass : 'Error',
	#instVars : [
		'validationResult'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'instance creation' }
CRInvalidRuntimeConfigurationException class >> validationResult: aValidationResult [
	^ self new validationResult: aValidationResult; yourself
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> validationResult [
	^ validationResult
]

{ #category : 'accessing' }
CRInvalidRuntimeConfigurationException >> validationResult: aValidationResult [
	validationResult := aValidationResult
]
