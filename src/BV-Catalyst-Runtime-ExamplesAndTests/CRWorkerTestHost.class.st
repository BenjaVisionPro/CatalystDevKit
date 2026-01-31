Class {
	#name : 'CRWorkerTestHost',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'process'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'instance creation' }
CRWorkerTestHost class >> onWorker: aWorker [
	^ self new
		worker: aWorker;
		yourself
]

{ #category : 'running' }
CRWorkerTestHost >> ensureStoppedUpToMSecs: timeoutMSecs [
	"Never leak a process across tests. Request stop, wait bounded, then terminate if needed."

	| startTime |
	process ifNil: [ ^ self ].

	self stop.
	startTime := Time millisecondClockValue.

	[ worker status == CRStatus stopped
		or: [ process isTerminated
				or: [ Time millisecondClockValue - startTime >= timeoutMSecs ] ] ]
		whileFalse: [ (Delay forMilliseconds: 1) wait ].

	process isTerminated not ifTrue: [ process terminate ].
	process := nil
]

{ #category : 'running' }
CRWorkerTestHost >> start [
	"Host the worker loop in a background Process. runLoop blocks."

	(process notNil and: [ process isTerminated not ]) ifTrue: [ ^ self ].

	process := [ worker start ] forkAt: Processor userBackgroundPriority
]

{ #category : 'running' }
CRWorkerTestHost >> stop [
	"Worker-level shutdown is graceful in your current worker shape."

	worker stop
]

{ #category : 'running' }
CRWorkerTestHost >> waitUntilRunningUpToMSecs: timeoutMSecs [
	| startTime |
	startTime := Time millisecondClockValue.

	[ worker status == CRStatus running
		or: [ Time millisecondClockValue - startTime >= timeoutMSecs ] ]
		whileFalse: [ (Delay forMilliseconds: 1) wait ].

	worker status == CRStatus running
		ifFalse: [ self error: 'Timed out waiting for worker to become running.' ]
]

{ #category : 'accessing' }
CRWorkerTestHost >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerTestHost >> worker: anObject [
	worker := anObject
]
