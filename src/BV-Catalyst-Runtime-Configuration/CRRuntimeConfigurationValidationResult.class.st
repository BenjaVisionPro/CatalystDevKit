Class {
	#name : 'CRRuntimeConfigurationValidationResult',
	#superclass : 'Object',
	#instVars : [
		'errors',
		'warnings'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'adding' }
CRRuntimeConfigurationValidationResult >> addError: aString [
	errors add: aString asString
]

{ #category : 'adding' }
CRRuntimeConfigurationValidationResult >> addWarning: aString [
	warnings add: aString asString
]

{ #category : 'accessing' }
CRRuntimeConfigurationValidationResult >> errors [
	^ errors
]

{ #category : 'initialization' }
CRRuntimeConfigurationValidationResult >> initialize [
	super initialize.
	errors := OrderedCollection new.
	warnings := OrderedCollection new
]

{ #category : 'testing' }
CRRuntimeConfigurationValidationResult >> isValid [
	^ errors isEmpty
]

{ #category : 'accessing' }
CRRuntimeConfigurationValidationResult >> warnings [
	^ warnings
]
