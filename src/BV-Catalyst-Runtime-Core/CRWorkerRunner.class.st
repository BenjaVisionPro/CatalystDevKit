Class {
	#name : 'CRWorkerRunner',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'process',
		'status'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkerRunner class >> onWorker: aWorker [
	^ self new
		worker: aWorker;
		yourself
]

{ #category : 'initialization' }
CRWorkerRunner >> initialize [
	super initialize.
	status := CRStatus stopped
]

{ #category : 'testing' }
CRWorkerRunner >> isRunning [
	^ process notNil and: [ process isTerminated not ]
]

{ #category : 'running' }
CRWorkerRunner >> start [
	(process notNil and: [ process isTerminated not ]) ifTrue: [ ^ self ].

	status := CRStatus startingUp.

	process := [ [ worker start ] ensure: [ status := CRStatus stopped ] ]
			forkAt: Processor userBackgroundPriority.

	status := CRStatus running
]

{ #category : 'accessing' }
CRWorkerRunner >> status [
	^ status
]

{ #category : 'running' }
CRWorkerRunner >> stop [
	"Graceful stop only: ask the worker to stop, then wait; if it won't die, terminate the process."

	process
		ifNil: [ status := CRStatus stopped.
			^ self ].

	status := CRStatus shuttingDown.
	worker stop.

	self waitForTerminationUpToMilliseconds: 2000.

	process isTerminated ifFalse: [ process terminate ].

	process := nil.
	status := CRStatus stopped
]

{ #category : 'running' }
CRWorkerRunner >> stopImmediate [
	"Immediate is purely environment-level: terminate the process."

	process
		ifNil: [ status := CRStatus stopped.
			^ self ].

	status := CRStatus shuttingDown.

	process isTerminated ifFalse: [ process terminate ].

	process := nil.
	status := CRStatus stopped
]

{ #category : 'running' }
CRWorkerRunner >> waitForTerminationUpToMilliseconds: timeoutMillis [
	| startTime |
	process ifNil: [ ^ self ].

	startTime := Time millisecondClockValue.
	[ process notNil
		and: [ process isTerminated not
				and: [ Time millisecondClockValue - startTime < timeoutMillis ] ] ]
		whileTrue: [ Processor yield ]
]

{ #category : 'accessing' }
CRWorkerRunner >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerRunner >> worker: anObject [
	worker := anObject
]
