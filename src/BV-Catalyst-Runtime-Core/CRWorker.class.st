Class {
	#name : 'CRWorker',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workQueue',
		'stopRequested'
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
	"I initialise my state."

	super initialize.
	displayName := 'Runtime Worker'.
	workQueue := CRWorkQueue new.
	stopRequested := false
]

{ #category : 'lifecycle' }
CRWorker >> requestStop [
	"I request that my run loop stops and I wake the queue so it can notice."

	stopRequested := true.
	workQueue enqueue: CRWakeupWorkUnit new
]

{ #category : 'running' }
CRWorker >> runLoop [
	"I run work items until I am asked to stop."

	[ stopRequested ]
		whileFalse: [ | work |
			work := workQueue next.
			work run ]
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
