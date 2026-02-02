Class {
	#name : 'CRWorker',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workQueue',
		'scheduler',
		'idleEnvelope',
		'status',
		'announcer',
		'services'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'accessing' }
CRWorker >> announcer [
	^ announcer
]

{ #category : 'accessing' }
CRWorker >> displayName [
	"I answer my display name."

	^ displayName
]

{ #category : 'accessing' }
CRWorker >> displayName: aString [
	"I set my display name."

	displayName := aString
]

{ #category : 'queue' }
CRWorker >> enqueue: aWorkUnit [
	"Public API: accept only while running."

	self isAcceptingWork
		ifFalse: [ (CRWorkerNotAcceptingWorkException
				worker: self
				workUnit: aWorkUnit
				reason: 'not running') signal ].

	^ workQueue enqueue: (self newEnvelopeFor: aWorkUnit)
]

{ #category : 'queue' }
CRWorker >> enqueueScheduled: aWorkUnit scheduleKey: aKey boundaryMillis: boundaryMillis [
	"Internal seam for the scheduler: envelope context is created at enqueue time."

	| envelope |
	envelope := self newEnvelopeFor: aWorkUnit.
	envelope context
		add: (CRScheduleContext key: aKey boundaryMillis: boundaryMillis).
	^ workQueue enqueue: envelope
]

{ #category : 'private - running' }
CRWorker >> executeWorkUnitInEnvelope: aWorkUnitEnvelope [
	| unit unitContext execContext scheduleContext requiredServiceClass |
	unit := aWorkUnitEnvelope workUnit.
	unitContext := aWorkUnitEnvelope context.

	execContext := CRWorkUnitExecutionContext
			worker: self
			envelope: aWorkUnitEnvelope.

	requiredServiceClass := unit class requiredWorkerServiceClass.
	requiredServiceClass
		ifNotNil: [ execContext
				service: (self services service: requiredServiceClass requiredByWorkUnitClass: unit class) ].

	[ [ unit executeWorkUnitInContext: execContext ]
		on: Error
		do: [ :ex | 
			announcer
				announce: (CRWorkUnitFailedAnnouncement
						worker: self
						workUnit: unit
						exception: ex) ] ]
		ensure: [  "Scheduler in-flight completion hook."scheduleContext := unitContext
					at: CRScheduleContext
					ifAbsent: [ nil ].
			scheduleContext ifNotNil: [ scheduler noteCompletedKey: scheduleContext key ] ]
]

{ #category : 'initialization' }
CRWorker >> initialize [
	super initialize.
	displayName := 'Runtime Worker'.
	workQueue := CRWorkQueue new.
	status := CRStatus stopped.
	announcer := CRAnnouncer new.
	scheduler := CRWorkScheduler new.
	services := CRServices onWorker: self.
	idleEnvelope := CRWorkUnitEnvelope onWorkUnit: CRIdleWorkUnit new
]

{ #category : 'testing' }
CRWorker >> isAcceptingWork [
	^ status == CRStatus running
]

{ #category : 'private - running' }
CRWorker >> minimumIdleMillis [
	"Config hook. Keep small; can be lifted to a configuration object later."

	^ 10
]

{ #category : 'private - queue' }
CRWorker >> newEnvelopeFor: aWorkUnit [
	^ CRWorkUnitEnvelope onWorkUnit: aWorkUnit
]

{ #category : 'private - running' }
CRWorker >> runLoop [
	| envelope timeout |
	status := CRStatus running.
	announcer announce: (CRWorkerStartedAnnouncement worker: self).

	[ [ true ]
		whileTrue: [ scheduler scheduleWorkOn: self.

			timeout := self timeoutMillisUntilNextWake.
			envelope := workQueue next: timeout ifNone: idleEnvelope.

			envelope == idleEnvelope
				ifTrue: [ self shouldExitAfterIdle ifTrue: [ ^ self ].
					self yieldExecution ]
				ifFalse: [ self executeWorkUnitInEnvelope: envelope ] ] ]
		ensure: [ self uninstallAllServices.
			status := CRStatus stopped.
			announcer announce: (CRWorkerStoppedAnnouncement worker: self) ]
]

{ #category : 'accessing' }
CRWorker >> scheduler [
	^ scheduler
]

{ #category : 'accessing' }
CRWorker >> services [
	^ services
]

{ #category : 'private - running' }
CRWorker >> shouldExitAfterIdle [
	"Exit rule: shutting down, scheduler suspended, and queue still empty after an idle wake."

	status == CRStatus shuttingDown ifFalse: [ ^ false ].
	scheduler millisecondsUntilNextDue = 0 ifFalse: [ ^ false ].
	^ workQueue nextOrNil isNil
]

{ #category : 'running' }
CRWorker >> start [
	"Block and run the worker loop until shutdown completes."

	^ self runLoop
]

{ #category : 'accessing' }
CRWorker >> status [
	^ status
]

{ #category : 'running' }
CRWorker >> stop [
	"Graceful shutdown only: stop scheduling new internal work, drain, then exit."

	status == CRStatus shuttingDown ifTrue: [ ^ self ].

	status := CRStatus shuttingDown.
	announcer announce: (CRWorkerShuttingDownAnnouncement worker: self).

	scheduler suspend
]

{ #category : 'private - running' }
CRWorker >> timeoutMillisUntilNextWake [
	"Wake either when the next scheduled work is due,
	or at least every minimumIdleMillis (for periodic loop progress)."

	| nextDue |
	(scheduler isSuspended and: [ status == CRStatus shuttingDown ])
		ifTrue: [ ^ 0 ].

	nextDue := scheduler millisecondsUntilNextDue.
	^ (nextDue min: self minimumIdleMillis) max: 0
]

{ #category : 'services' }
CRWorker >> uninstallAllServices [
	services uninstallAll
]

{ #category : 'running' }
CRWorker >> yieldExecution [
	"Idle behaviour: yield so we don’t burn CPU.
	We can tune this later or replace with a policy object."

	Processor yield
]
