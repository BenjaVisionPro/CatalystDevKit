Class {
	#name : 'CRRepeatingSchedule',
	#superclass : 'CRWorkSchedule',
	#instVars : [
		'intervalMillis'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRRepeatingSchedule class >> workUnitFactory: aBlock key: aKey intervalMillis: anIntervalMillis [
	^ self new
		workUnitFactory: aBlock;
		key: aKey;
		intervalMillis: anIntervalMillis;
		scheduledMillis: Time millisecondClockValue;
		initializeLastScheduledMillis;
		yourself
]

{ #category : 'accessing' }
CRRepeatingSchedule >> currentBoundaryMillis [
	| now elapsed slot |
	now := Time millisecondClockValue.
	elapsed := now - scheduledMillis.
	slot := elapsed // intervalMillis.
	^ scheduledMillis + (slot * intervalMillis)
]

{ #category : 'initialization' }
CRRepeatingSchedule >> initializeLastScheduledMillis [
	"Boundary 0 is considered handled so the first due is at +interval."

	lastScheduledMillis := scheduledMillis
]

{ #category : 'accessing' }
CRRepeatingSchedule >> intervalMillis [
	^ intervalMillis
]

{ #category : 'accessing' }
CRRepeatingSchedule >> intervalMillis: anObject [
	intervalMillis := anObject
]

{ #category : 'testing' }
CRRepeatingSchedule >> isDueNow [
	^ self currentBoundaryMillis > lastScheduledMillis
]

{ #category : 'updating' }
CRRepeatingSchedule >> markHandledBoundaryMillis: boundaryMillis [
	lastScheduledMillis := boundaryMillis
]

{ #category : 'accessing' }
CRRepeatingSchedule >> millisecondsUntilNextDue [
	| now elapsed remainder |
	now := Time millisecondClockValue.
	elapsed := now - scheduledMillis.
	remainder := elapsed \\ intervalMillis.
	^ intervalMillis - remainder
]
