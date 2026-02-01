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
CRWorkScheduleDeliveryConfiguration >> validateOn: result forWorkerIdentifier: workerIdentifier scheduleIdentifier: scheduleIdentifier [
	| workerLabel scheduleLabel |
	workerLabel := workerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ workerIdentifier printString ].

	scheduleLabel := scheduleIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ scheduleIdentifier printString ].

	overlapBehaviour isNil
		ifTrue: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' delivery overlapBehaviour is required.' ].

	missedBehaviour isNil
		ifTrue: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' delivery missedBehaviour is required.' ]
]
