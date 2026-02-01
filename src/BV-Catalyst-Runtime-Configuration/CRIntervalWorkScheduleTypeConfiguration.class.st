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
CRIntervalWorkScheduleTypeConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier scheduleIdentifier: aScheduleIdentifier [
	| workerLabel scheduleLabel |
	workerLabel := aWorkerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ aWorkerIdentifier printString ].

	scheduleLabel := aScheduleIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ aScheduleIdentifier printString ].

	(intervalMillis isInteger and: [ intervalMillis > 0 ])
		ifFalse: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' intervalMillis must be a positive Integer; got '
						, intervalMillis printString , ' (' , intervalMillis class name , ').' ]
]
