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

{ #category : 'accessing' }
CRRepeatingSchedule >> currentBoundaryMillisAtMillis: nowMillis [
	| elapsed k |
	elapsed := nowMillis - scheduledMillis.
	elapsed < 0 ifTrue: [ ^ scheduledMillis ].
	k := elapsed // intervalMillis.
	^ scheduledMillis + (k * intervalMillis)
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
CRRepeatingSchedule >> intervalMillis: anInteger [
	(anInteger isInteger and: [ anInteger > 0 ])
		ifFalse: [ self error: 'intervalMillis must be a positive integer.' ].
	intervalMillis := anInteger
]

{ #category : 'testing' }
CRRepeatingSchedule >> isDueAtMillis: nowMillis [
	^ (self millisecondsUntilNextDueAtMillis: nowMillis) = 0
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

{ #category : 'accessing' }
CRRepeatingSchedule >> millisecondsUntilNextDueAtMillis: nowMillis [
	| elapsed remainder |
	intervalMillis <= 0 ifTrue: [ self error: 'intervalMillis must be positive.' ].
	elapsed := nowMillis - scheduledMillis.
	elapsed < 0 ifTrue: [ ^ scheduledMillis - nowMillis ].	
	
	"not reached boundary yet"
	remainder := elapsed \\ intervalMillis.
	^ remainder = 0 ifTrue: [ 0 ] ifFalse: [ intervalMillis - remainder ]
]
