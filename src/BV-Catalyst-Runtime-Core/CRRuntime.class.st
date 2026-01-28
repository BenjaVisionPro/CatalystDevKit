Class {
	#name : 'CRRuntime',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workers',
		'runners',
		'isRunning'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'workers' }
CRRuntime >> addWorker: aWorker [
	"I register a worker. If I am running, I also start it via its runner."

	workers add: aWorker.
	isRunning ifTrue: [ self ensureRunnerStartedFor: aWorker ].
	^ aWorker
]

{ #category : 'workers' }
CRRuntime >> createRunnerFor: aWorker [
	"I create a runner for the worker."

	^ CRWorkerRunner new
		worker: aWorker;
		yourself
]

{ #category : 'accessing' }
CRRuntime >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CRRuntime >> displayName: anObject [
	displayName := anObject
]

{ #category : 'workers' }
CRRuntime >> ensureRunnerStartedFor: aWorker [
	"I ensure the given worker has a runner and that it is started."

	| runner |
	runner := runners at: aWorker ifAbsentPut: [ self createRunnerFor: aWorker ].
	runner start.
	^ runner
]

{ #category : 'initialization' }
CRRuntime >> initialize [
	"I initialise my state."

	super initialize.
	displayName := 'Catalyst Runtime'.
	workers := OrderedCollection new.
	runners := IdentityDictionary new.
	isRunning := false
]

{ #category : 'accessing' }
CRRuntime >> isRunning [
	^ isRunning
]

{ #category : 'private' }
CRRuntime >> registry [
	"I answer the registry used for tracking runtimes (dev/GT)."

	^ CRRuntimeRegistry default
]

{ #category : 'workers' }
CRRuntime >> removeWorker: aWorker [
	"I remove a worker and stop its runner if present."

	| runner |
	runner := runners removeKey: aWorker ifAbsent: [ nil ].
	runner ifNotNil: [ runner stop ].
	workers remove: aWorker ifAbsent: [  ].
	^ aWorker
]

{ #category : 'accessing' }
CRRuntime >> runners [
	^ runners
]

{ #category : 'lifecycle' }
CRRuntime >> start [
	"I start my runtime and all registered workers."

	isRunning ifTrue: [ ^ self ].

	isRunning := true.
	self registry register: self.

	workers do: [ :w | self ensureRunnerStartedFor: w ].
	^ self
]

{ #category : 'lifecycle' }
CRRuntime >> stop [
	"I stop all workers and unregister myself."

	isRunning ifFalse: [ ^ self ].

	[ runners valuesDo: [ :runner | runner stop ].
	runners := IdentityDictionary new.
	isRunning := false ] ensure: [ self registry unregister: self ].
	^ self
]

{ #category : 'workers' }
CRRuntime >> workers [
	"I answer my workers."

	^ workers copy
]
