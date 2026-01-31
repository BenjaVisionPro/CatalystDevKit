Class {
	#name : 'CRWorker',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workQueue',
		'stopRequested',
		'stopMode',
		'status',
		'announcer'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'accessing' }
CRWorker >> announcer [
	^ announcer
]

{ #category : 'queue' }
CRWorker >> basicEnqueue: aUnit [
	"Internal enqueue. No acceptance checks.
	Used for lifecycle wakeups so shutdown can always break a blocking wait."

	workQueue enqueue: aUnit.
	^ aUnit
]

{ #category : 'testing' }
CRWorker >> canAcceptWork [
	"External acceptance rule: only accept while running and not shutting down."

	status == CRStatus running ifFalse: [ ^ false ].
	^ stopMode == CRStopMode none
]

{ #category : 'accessing' }
CRWorker >> displayName [
	"I answer my display name."

	^ displayName
]

{ #category : 'accessing' }
CRWorker >> displayName: aString [
	"I set my display name."

	displayName := aString asString
]

{ #category : 'queue' }
CRWorker >> enqueue: aUnit [
	"I enqueue external work.
	If I am not accepting work, I signal a typed exception carrying worker + unit."

	self canAcceptWork
		ifFalse: [ (CRWorkerNotAcceptingWorkException
				worker: self
				unit: aUnit
				reason: self notAcceptingWorkReason) signal ].

	^ self basicEnqueue: aUnit
]

{ #category : 'running' }
CRWorker >> executeUnit: aUnit [
	[ aUnit run ]
		on: Error
		do: [ :ex |
			announcer announce: (CRWorkUnitFailedAnnouncement
				worker: self
				unit: aUnit
				exception: ex) ].
]

{ #category : 'initialization' }
CRWorker >> initialize [
	displayName := 'Runtime Worker'.
	workQueue := CRWorkQueue new.
	stopMode := CRStopMode none.
	status := CRStatus stopped.
	announcer := CRAnnouncer new.
]

{ #category : 'lifecycle' }
CRWorker >> notAcceptingWorkReason [
	status == CRStatus running ifFalse: [ ^ 'not running' ].
	stopMode == CRStopMode none ifFalse: [ ^ 'shutting down' ].
	^ 'not accepting work'
]

{ #category : 'lifecycle' }
CRWorker >> requestGracefulStop [
	stopMode := CRStopMode graceful.
	status := CRStatus shuttingDown.
	announcer announce: (CRWorkerShuttingDownAnnouncement worker: self).
]

{ #category : 'lifecycle' }
CRWorker >> requestImmediateStop [
	stopMode := CRStopMode immediate.
	status := CRStatus shuttingDown.
	announcer announce: (CRWorkerShuttingDownAnnouncement worker: self).
]

{ #category : 'running' }
CRWorker >> runLoop [
	| work |
	status := CRStatus running.
	announcer announce: (CRWorkerStartedAnnouncement worker: self).

	[ [ true ]
		whileTrue: [ stopMode == CRStopMode immediate ifTrue: [ ^ self ].

			work := workQueue nextOrNil.

			work
				ifNil: [ stopMode == CRStopMode graceful ifTrue: [ ^ self ].
					self yieldExecution	"continue" ]
				ifNotNil: [ self executeUnit: work ] ] ]
		ensure: [ status := CRStatus stopped.
			stopMode := CRStopMode none.
			announcer announce: (CRWorkerStoppedAnnouncement worker: self) ]
]

{ #category : 'accessing' }
CRWorker >> status [
	^ status
]

{ #category : 'running' }
CRWorker >> yieldExecution [
	"Idle behaviour: yield so we don’t burn CPU.
	We can tune this later or replace with a policy object."

	Processor yield
]
