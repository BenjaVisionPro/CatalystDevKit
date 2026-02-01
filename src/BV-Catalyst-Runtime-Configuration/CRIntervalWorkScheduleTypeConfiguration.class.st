Class {
	#name : 'CRIntervalWorkScheduleTypeConfiguration',
	#superclass : 'CRWorkScheduleTypeConfiguration',
	#instVars : [
		'intervalMillis'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRIntervalWorkScheduleTypeConfiguration >> initialize [
	super initialize.
	intervalMillis := 0
]

{ #category : 'accessing' }
CRIntervalWorkScheduleTypeConfiguration >> intervalMillis [
	^ intervalMillis
]

{ #category : 'accessing' }
CRIntervalWorkScheduleTypeConfiguration >> intervalMillis: anInteger [
	intervalMillis := anInteger asInteger
]

{ #category : 'validation' }
CRIntervalWorkScheduleTypeConfiguration >> validateOn: aValidationResult forScheduleIdentifier: aScheduleIdentifier workerIdentifier: aWorkerIdentifier [
	(intervalMillis isInteger and: [ intervalMillis > 0 ])
		ifFalse: [ aValidationResult addError: 'Schedule ', aScheduleIdentifier printString, ' on worker ', aWorkerIdentifier printString, ' must have intervalMillis > 0.' ].
]
