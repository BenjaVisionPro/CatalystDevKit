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
	suspended ifTrue: [ ^ 0 ].
	schedules isEmpty ifTrue: [ ^ SmallInteger maxVal ].
	^ (schedules collect: [ :each | each millisecondsUntilNextDue ]) min
]

{ #category : 'running' }
CRWorkScheduler >> noteCompletedKey: aKey [
	inFlightByKey at: aKey put: false
]

{ #category : 'running' }
CRWorkScheduler >> resume [
	suspended := false
]

{ #category : 'running' }
CRWorkScheduler >> scheduleWorkOn: aWorker [
	"Called by the worker each loop iteration.
	Phase-locked repeating. Skip if in-flight."

	suspended ifTrue: [ ^ self ].

	schedules
		do: [ :schedule | 
			schedule isDueNow
				ifTrue: [ | boundary key |
					boundary := schedule currentBoundaryMillis.
					key := schedule key.

					(inFlightByKey at: key ifAbsent: [ false ])
						ifTrue: [  
						   "Skip this occurrence; still mark handled so we don't retry this boundary."schedule
								markHandledBoundaryMillis: boundary ]
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
