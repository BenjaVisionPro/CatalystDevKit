Class {
	#name : 'CRWorkScheduleConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'scheduleTypeConfiguration',
		'workUnitClassName',
		'deliveryConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> deliveryConfiguration [
	^ deliveryConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> deliveryConfiguration: aCRWorkScheduleDeliveryConfiguration [
	deliveryConfiguration := aCRWorkScheduleDeliveryConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> identifier [
	^ identifier
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> identifier: anObject [
	identifier := anObject
]

{ #category : 'initialization' }
CRWorkScheduleConfiguration >> initialize [
	super initialize.
	identifier := nil.
	scheduleTypeConfiguration := nil.
	workUnitClassName := ''.
	deliveryConfiguration := nil
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> scheduleTypeConfiguration [
	^ scheduleTypeConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> scheduleTypeConfiguration: aCRWorkScheduleTypeConfiguration [
	scheduleTypeConfiguration := aCRWorkScheduleTypeConfiguration
]

{ #category : 'validation' }
CRWorkScheduleConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier [
	(identifier isNil or: [ identifier asString isEmpty ])
		ifTrue: [ aValidationResult addError: 'Schedule identifier is required on worker ', aWorkerIdentifier printString, '.' ].
	workUnitClassName isEmpty ifTrue: [ aValidationResult addError: 'Schedule ', identifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify a work unit class name.' ].
	scheduleTypeConfiguration
		ifNil: [ aValidationResult addError: 'Schedule ', identifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify a schedule type.' ]
		ifNotNil: [ scheduleTypeConfiguration validateOn: aValidationResult forScheduleIdentifier: identifier workerIdentifier: aWorkerIdentifier ].
	deliveryConfiguration
		ifNil: [ aValidationResult addError: 'Schedule ', identifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify delivery configuration.' ]
		ifNotNil: [ deliveryConfiguration validateOn: aValidationResult forScheduleIdentifier: identifier workerIdentifier: aWorkerIdentifier ].
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClassName [
	^ workUnitClassName
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClassName: aString [
	workUnitClassName := aString asString
]
