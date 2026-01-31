Class {
	#name : 'CRInlineWorkerRunner',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'status'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'instance creation' }
CRInlineWorkerRunner class >> on: aWorker [
	^ self new
		worker: aWorker;
		yourself
]

{ #category : 'testing' }
CRInlineWorkerRunner >> isRunning [
	^ self status == CRStatus running
]

{ #category : 'running' }
CRInlineWorkerRunner >> runOnce [
	"Run exactly one available unit in the current process."

	self isRunning
		ifFalse: [ self error: 'Runner must be started before running work.' ].
	^ worker runOnce
]

{ #category : 'lifecycle' }
CRInlineWorkerRunner >> start [
	"Enter a known running state without forking a background process.
	This is intentionally deterministic for tests/examples."

	self isRunning ifTrue: [ ^ self ].

	status := CRStatus running.
	worker privateSetStatus: CRStatus running
]

{ #category : 'accessing' }
CRInlineWorkerRunner >> status [
	^ status ifNil: [ CRStatus stopped ]
]

{ #category : 'accessing' }
CRInlineWorkerRunner >> status: anObject [
	status := anObject
]

{ #category : 'lifecycle' }
CRInlineWorkerRunner >> stop [
	"Default stop = graceful."

	^ self stopGraceful
]

{ #category : 'lifecycle' }
CRInlineWorkerRunner >> stopGraceful [
	self isRunning ifFalse: [ ^ self ].

	status := CRStatus shuttingDown.
	worker requestGracefulStop.	
	
	"Inline runner is not pumping a loop, so stopping is a state transition only."
	status := CRStatus stopped.
	worker privateSetStatus: CRStatus stopped
]

{ #category : 'lifecycle' }
CRInlineWorkerRunner >> stopImmediate [
	self isRunning ifFalse: [ ^ self ].

	status := CRStatus shuttingDown.
	worker requestImmediateStop.

	status := CRStatus stopped.
	worker status: CRStatus stopped
]

{ #category : 'accessing' }
CRInlineWorkerRunner >> worker [
	^ worker
]

{ #category : 'accessing' }
CRInlineWorkerRunner >> worker: anObject [
	worker := anObject
]
