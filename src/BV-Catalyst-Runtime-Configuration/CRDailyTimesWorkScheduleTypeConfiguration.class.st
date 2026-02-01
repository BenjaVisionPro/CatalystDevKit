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
CRDailyTimesWorkScheduleTypeConfiguration >> validateOn: result forWorkerIdentifier: workerIdentifier scheduleIdentifier: scheduleIdentifier [
	timesOfDay isEmpty
		ifTrue: [ result
				addError: 'Daily schedule ' , scheduleIdentifier printString , ' on worker '
						, workerIdentifier printString
						, ' must specify at least one time of day.' ]
]
