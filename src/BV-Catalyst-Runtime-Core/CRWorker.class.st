Class {
	#name : 'CRWorker',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workQueue',
		'stopRequested',
		'stopMode',
		'status'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

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

{ #category : 'initialization' }
CRWorker >> initialize [
	displayName := 'Runtime Worker'.
	workQueue := CRWorkQueue new.
	stopMode := CRStopMode none.
	status := CRStatus stopped
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
	self basicEnqueue: CRWakeupWorkUnit new
]

{ #category : 'lifecycle' }
CRWorker >> requestImmediateStop [
	stopMode := CRStopMode immediate.
	status := CRStatus shuttingDown.
	self basicEnqueue: CRWakeupWorkUnit new
]

{ #category : 'lifecycle' }
CRWorker >> requestStop [
	"Compatibility: default is graceful."

	^ self requestGracefulStop
]

{ #category : 'running' }
CRWorker >> runLoop [
	| work |
	status := CRStatus running.

	[ [ true ]
		whileTrue: [ stopMode == CRStopMode immediate ifTrue: [ ^ self ].

			stopMode == CRStopMode graceful
				ifTrue: [ work := workQueue nextOrNil.
					work ifNil: [ ^ self ] ]
				ifFalse: [ work := workQueue next ].

			work run ] ]
		ensure: [ status := CRStatus stopped.
			stopMode := CRStopMode none ]
]

{ #category : 'running' }
CRWorker >> runOnce [
	"I run at most one available work item and answer whether I ran one."

	| work |
	work := workQueue nextOrNil.
	work ifNil: [ ^ false ].
	work run.
	^ true
]

{ #category : 'accessing' }
CRWorker >> status [
	^ status
]
