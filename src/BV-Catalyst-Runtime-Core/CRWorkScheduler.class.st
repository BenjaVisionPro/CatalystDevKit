Class {
	#name : 'CRWorkScheduler',
	#superclass : 'Object',
	#instVars : [
		'schedules',
		'inFlightByKey',
		'suspended'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'schedules' }
CRWorkScheduler >> addSchedule: aSchedule [
	schedules add: aSchedule.
	^ aSchedule
]

{ #category : 'time' }
CRWorkScheduler >> currentMillis [
	^ Time millisecondClockValue
]

{ #category : 'initialization' }
CRWorkScheduler >> initialize [
	super initialize.
	schedules := OrderedCollection new.
	inFlightByKey := Dictionary new.
	suspended := false
]

{ #category : 'testing' }
CRWorkScheduler >> isSuspended [
	^ suspended
]

{ #category : 'testing' }
CRWorkScheduler >> millisecondsUntilNextDue [
	| now |
	suspended ifTrue: [ ^ 0 ].
	schedules isEmpty ifTrue: [ ^ 0 ].

	now := self currentMillis.
	^ (schedules collect: [ :each | each millisecondsUntilNextDueAtMillis: now ])
		min
]

{ #category : 'running' }
CRWorkScheduler >> noteCompletedKey: aKey [
	inFlightByKey removeKey: aKey ifAbsent: [  ]
]

{ #category : 'running' }
CRWorkScheduler >> resume [
	suspended := false
]

{ #category : 'running' }
CRWorkScheduler >> scheduleWorkOn: aWorker [
	| now |
	suspended ifTrue: [ ^ self ].
	now := self currentMillis.

	schedules
		do: [ :schedule | 
			| key boundary |
			(schedule isDueAtMillis: now)
				ifTrue: [ key := schedule key.
					boundary := schedule currentBoundaryMillisAtMillis: now.

					(inFlightByKey at: key ifAbsent: [ false ])
						ifTrue: [  "skip - already in flight" ]
						ifFalse: [ inFlightByKey at: key put: true.
							schedule markHandledBoundaryMillis: boundary.
							aWorker
								enqueueScheduled: schedule newWorkUnit
								scheduleKey: key
								boundaryMillis: boundary ] ] ]
]

{ #category : 'running' }
CRWorkScheduler >> suspend [
	suspended := true
]
