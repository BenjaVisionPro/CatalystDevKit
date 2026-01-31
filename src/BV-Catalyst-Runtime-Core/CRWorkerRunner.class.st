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
CRWorkerRunner class >> worker: aWorker [
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
	"Truth is process-backed, but we also maintain #status."

	^ process notNil and: [ process isActive ]
]

{ #category : 'running' }
CRWorkerRunner >> start [
	(process notNil and: [ process isTerminated not ]) ifTrue: [ ^ self ].

	status := CRStatus startingUp.

	process := [ [ worker runLoop ] ensure: [ status := CRStatus stopped ] ]
			forkAt: Processor userBackgroundPriority.

	status := CRStatus running
]

{ #category : 'accessing' }
CRWorkerRunner >> status [
	^ status
]

{ #category : 'running' }
CRWorkerRunner >> stop [
	"Compatibility: default is graceful."

	^ self stopGraceful
]

{ #category : 'running' }
CRWorkerRunner >> stopGraceful [
	process
		ifNil: [ status := CRStatus stopped.
			^ self ].

	status := CRStatus shuttingDown.
	worker requestGracefulStop.

	self waitForTerminationUpToMilliseconds: 2000 pollingEveryMilliseconds: 10.
	process isTerminated ifFalse: [ process terminate ].

	process := nil.
	status := CRStatus stopped
]

{ #category : 'running' }
CRWorkerRunner >> stopImmediate [ 
	process ifNil: [ status := CRStatus stopped. ^ self ].

	status := CRStatus shuttingDown.
	worker requestImmediateStop.

	"Immediate means: don't wait."
	process isTerminated ifFalse: [ process terminate ].

	process := nil.
	status := CRStatus stopped
]

{ #category : 'running' }
CRWorkerRunner >> waitForTerminationUpToMilliseconds: maxMillis pollingEveryMilliseconds: pollMillis [
	| waited |
	waited := 0.
	[ process notNil and: [ process isTerminated not and: [ waited < maxMillis ] ] ]
		whileTrue: [ (Delay forMilliseconds: pollMillis) wait.
			waited := waited + pollMillis ]
]

{ #category : 'accessing' }
CRWorkerRunner >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerRunner >> worker: anObject [
	worker := anObject
]
