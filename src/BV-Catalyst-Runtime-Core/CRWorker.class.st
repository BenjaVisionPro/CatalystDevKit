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
CRWorker >> enqueue: aWorkItem [
	"I enqueue a work item for execution."

	^ workQueue enqueue: aWorkItem
]

{ #category : 'initialization' }
CRWorker >> initialize [
	displayName := 'Runtime Worker'.
	workQueue := CRWorkQueue new.
	stopMode := CRStopMode none.
	status := CRStatus stopped
]

{ #category : 'lifecycle' }
CRWorker >> requestGracefulStop [
	stopMode == CRStopMode immediate ifTrue: [ ^ self ].
	stopMode := CRStopMode graceful.
	status := CRStatus shuttingDown.
	workQueue enqueue: CRWakeupWorkUnit new
]

{ #category : 'lifecycle' }
CRWorker >> requestImmediateStop [
	stopMode := CRStopMode immediate.
	status := CRStatus shuttingDown.
	workQueue enqueue: CRWakeupWorkUnit new
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
