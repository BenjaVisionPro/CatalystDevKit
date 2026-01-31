Class {
	#name : 'CRWorkSchedule',
	#superclass : 'Object',
	#instVars : [
		'key',
		'scheduledMillis',
		'lastScheduledMillis',
		'workUnitFactory'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'accessing' }
CRWorkSchedule >> key [
	^ key
]

{ #category : 'accessing' }
CRWorkSchedule >> key: anObject [
	key := anObject
]

{ #category : 'accessing' }
CRWorkSchedule >> lastScheduledMillis [
	^ lastScheduledMillis
]

{ #category : 'accessing' }
CRWorkSchedule >> lastScheduledMillis: anObject [
	lastScheduledMillis := anObject
]

{ #category : 'factory' }
CRWorkSchedule >> newWorkUnit [
	^ workUnitFactory value
]

{ #category : 'accessing' }
CRWorkSchedule >> scheduledMillis [
	^ scheduledMillis
]

{ #category : 'accessing' }
CRWorkSchedule >> scheduledMillis: anObject [
	scheduledMillis := anObject
]

{ #category : 'accessing' }
CRWorkSchedule >> workUnitFactory [
	^ workUnitFactory
]

{ #category : 'accessing' }
CRWorkSchedule >> workUnitFactory: anObject [
	workUnitFactory := anObject
]
