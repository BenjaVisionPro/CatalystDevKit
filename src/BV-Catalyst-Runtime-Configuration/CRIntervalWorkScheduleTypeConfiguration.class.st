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
CRIntervalWorkScheduleTypeConfiguration >> validateOn: result forWorkerIdentifier: workerIdentifier scheduleIdentifier: scheduleIdentifier [
	| workerLabel scheduleLabel |
	workerLabel := workerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ workerIdentifier printString ].

	scheduleLabel := scheduleIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ scheduleIdentifier printString ].

	(intervalMillis isInteger and: [ intervalMillis > 0 ])
		ifFalse: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' intervalMillis must be a positive Integer; got '
						, intervalMillis printString , ' (' , intervalMillis class name , ').' ]
]
