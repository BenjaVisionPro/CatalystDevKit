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
CRWorkScheduleDeliveryConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier scheduleIdentifier: aScheduleIdentifier [
	| workerLabel scheduleLabel |
	workerLabel := aWorkerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ aWorkerIdentifier printString ].

	scheduleLabel := aScheduleIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ aScheduleIdentifier printString ].

	overlapBehaviour isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' delivery overlapBehaviour is required.' ].

	missedBehaviour isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' delivery missedBehaviour is required.' ]
]
