Class {
	#name : 'CRWorkerServiceConfiguration',
	#superclass : 'Object',
	#instVars : [
		'serviceClass',
		'configuration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'instance creation' }
CRWorkerServiceConfiguration class >> serviceClass: aServiceClass [
	^ self serviceClass: aServiceClass configuration: nil
]

{ #category : 'instance creation' }
CRWorkerServiceConfiguration class >> serviceClass: aServiceClass configuration: aConfiguration [
	^ self new
		serviceClass: aServiceClass;
		configuration: aConfiguration;
		yourself
]

{ #category : 'accessing' }
CRWorkerServiceConfiguration >> configuration [
	^ configuration
]

{ #category : 'accessing' }
CRWorkerServiceConfiguration >> configuration: anObject [
	configuration := anObject
]

{ #category : 'accessing' }
CRWorkerServiceConfiguration >> serviceClass [
	^ serviceClass
]

{ #category : 'accessing' }
CRWorkerServiceConfiguration >> serviceClass: anObject [
	serviceClass := anObject
]

{ #category : 'validation' }
CRWorkerServiceConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier [
	serviceClass isClass
		ifFalse: [ aValidationResult
				addError: 'Worker ' , aWorkerIdentifier printString
						, ' serviceClass must be a Class. Got ' , serviceClass printString , '.' ]
		ifTrue: [ (serviceClass inheritsFrom: CRWorkerService)
				ifFalse: [ aValidationResult
						addError: 'Worker ' , aWorkerIdentifier printString , ' serviceClass ' , serviceClass name
								, ' must inherit from CRWorkerService.' ] ]
]
