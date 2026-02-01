Class {
	#name : 'CRRuntimeOrchestratorClassMismatchException',
	#superclass : 'CRException',
	#instVars : [
		'currentClass',
		'requestedClass'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRRuntimeOrchestratorClassMismatchException class >> currentClass: aCurrentClass requestedClass: aRequestedClass [
	^ self new
		currentClass: aCurrentClass;
		requestedClass: aRequestedClass;
		yourself
]

{ #category : 'accessing' }
CRRuntimeOrchestratorClassMismatchException >> currentClass [
	^ currentClass
]

{ #category : 'accessing' }
CRRuntimeOrchestratorClassMismatchException >> currentClass: anObject [
	currentClass := anObject
]

{ #category : 'accessing' }
CRRuntimeOrchestratorClassMismatchException >> requestedClass [
	^ requestedClass
]

{ #category : 'accessing' }
CRRuntimeOrchestratorClassMismatchException >> requestedClass: anObject [
	requestedClass := anObject
]
