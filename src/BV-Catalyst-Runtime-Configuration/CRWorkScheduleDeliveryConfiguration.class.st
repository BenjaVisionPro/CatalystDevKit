Class {
	#name : 'CRWorkScheduleDeliveryConfiguration',
	#superclass : 'Object',
	#instVars : [
		'overlapBehaviour',
		'missedBehaviour'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRWorkScheduleDeliveryConfiguration >> initialize [
	super initialize.
	overlapBehaviour := nil.
	missedBehaviour := nil
]

{ #category : 'accessing' }
CRWorkScheduleDeliveryConfiguration >> missedBehaviour [
	^ missedBehaviour
]

{ #category : 'accessing' }
CRWorkScheduleDeliveryConfiguration >> missedBehaviour: anObject [
	missedBehaviour := anObject
]

{ #category : 'accessing' }
CRWorkScheduleDeliveryConfiguration >> overlapBehaviour [
	^ overlapBehaviour
]

{ #category : 'accessing' }
CRWorkScheduleDeliveryConfiguration >> overlapBehaviour: anObject [
	overlapBehaviour := anObject
]

{ #category : 'validation' }
CRWorkScheduleDeliveryConfiguration >> validateOn: aValidationResult forScheduleIdentifier: aScheduleIdentifier workerIdentifier: aWorkerIdentifier [
	overlapBehaviour ifNil: [ aValidationResult addError: 'Schedule ', aScheduleIdentifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify overlap behaviour.' ].
	missedBehaviour ifNil: [ aValidationResult addError: 'Schedule ', aScheduleIdentifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify missed behaviour.' ].
]
