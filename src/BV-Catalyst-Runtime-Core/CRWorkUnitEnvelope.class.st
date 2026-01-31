Class {
	#name : 'CRWorkUnitEnvelope',
	#superclass : 'Object',
	#instVars : [
		'workUnit',
		'context'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkUnitEnvelope class >> onWorkUnit: aWorkUnit [
	^ self new
		workUnit: aWorkUnit;
		context: CRWorkUnitContext new;
		yourself
]

{ #category : 'accessing' }
CRWorkUnitEnvelope >> context [
	^ context
]

{ #category : 'accessing' }
CRWorkUnitEnvelope >> context: anObject [
	context := anObject
]

{ #category : 'accessing' }
CRWorkUnitEnvelope >> workUnit [
	^ workUnit
]

{ #category : 'accessing' }
CRWorkUnitEnvelope >> workUnit: anObject [
	workUnit := anObject
]
