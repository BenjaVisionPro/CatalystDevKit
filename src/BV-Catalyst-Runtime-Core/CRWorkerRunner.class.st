Class {
	#name : 'CRWorkerRunner',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'process'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'running' }
CRWorkerRunner >> start [
	"I start running my worker in a background process."

	process ifNotNil: [ ^ self ].

	process := [ worker runLoop ] forkAt: Processor userBackgroundPriority
]

{ #category : 'running' }
CRWorkerRunner >> stop [
	"I ask my worker to stop and I terminate the process only as a safety net.
	TODO: Replace the fixed delay with a join/wait policy once we have one."

	process ifNil: [ ^ self ].

	worker requestStop.

	(Delay forMilliseconds: 50) wait.
	process isTerminated ifFalse: [ process terminate ].

	process := nil
]

{ #category : 'accessing' }
CRWorkerRunner >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerRunner >> worker: anObject [
	worker := anObject
]
