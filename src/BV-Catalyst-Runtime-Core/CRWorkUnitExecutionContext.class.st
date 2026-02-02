Class {
	#name : 'CRWorkUnitExecutionContext',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'envelope',
		'services',
		'service'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkUnitExecutionContext class >> worker: aWorker envelope: aWorkUnitEnvelope [
	^ self new
		worker: aWorker;
		envelope: aWorkUnitEnvelope;
		services: aWorker services;
		yourself
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> envelope [
	^ envelope
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> envelope: anObject [
	envelope := anObject
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> service [
	service
		ifNil: [ self
				error: 'Work unit attempted to access service but none was set on the execution context.' ].
	^ service
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> service: anObject [
	service := anObject
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> services [
	^ services
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> services: anObject [
	services := anObject
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkUnitExecutionContext >> worker: anObject [
	worker := anObject
]
