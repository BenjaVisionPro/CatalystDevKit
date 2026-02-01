Class {
	#name : 'CRDailyTimesWorkScheduleTypeConfiguration',
	#superclass : 'CRWorkScheduleTypeConfiguration',
	#instVars : [
		'timesOfDay'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRDailyTimesWorkScheduleTypeConfiguration >> initialize [
	super initialize.
	timesOfDay := OrderedCollection new
]

{ #category : 'accessing' }
CRDailyTimesWorkScheduleTypeConfiguration >> timesOfDay [
	^ timesOfDay
]

{ #category : 'accessing' }
CRDailyTimesWorkScheduleTypeConfiguration >> timesOfDay: aCollection [
	timesOfDay := aCollection asOrderedCollection
]

{ #category : 'validation' }
CRDailyTimesWorkScheduleTypeConfiguration >> validateOn: aValidationResult forScheduleIdentifier: aScheduleIdentifier workerIdentifier: aWorkerIdentifier [
	timesOfDay isEmpty ifTrue: [ aValidationResult addError: 'Daily schedule ', aScheduleIdentifier printString, ' on worker ', aWorkerIdentifier printString, ' must specify at least one time of day.' ].
]
