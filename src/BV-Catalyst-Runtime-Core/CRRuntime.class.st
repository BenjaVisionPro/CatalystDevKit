Class {
	#name : 'CRRuntime',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workers',
		'runners',
		'isRunning',
		'announcer'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'workers' }
CRRuntime >> addWorker: aWorker [
	"I add a worker to my runtime. I announce that the worker was added."

	workers add: aWorker.
	self announcer
		announce: (CRRuntimeWorkerAddedAnnouncement runtime: self worker: aWorker).

	isRunning ifTrue: [ self ensureRunnerStartedFor: aWorker ].
	^ aWorker
]

{ #category : 'announcer api' }
CRRuntime >> announce: anAnnouncement [
	"I announce through my channel-gated announcer."

	^ self announcer announce: anAnnouncement
]

{ #category : 'accessing' }
CRRuntime >> announcer [
	^ announcer
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
	announcer := CRAnnouncer new.
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
	"I remove a worker from my runtime. I stop its runner if present and announce removal."

	(runners at: aWorker ifAbsent: [ nil ])
		ifNotNil: [ :runner | 
			runner stop.
			runners removeKey: aWorker ifAbsent: [  ] ].

	workers remove: aWorker ifAbsent: [  ].

	self announcer
		announce: (CRRuntimeWorkerRemovedAnnouncement runtime: self worker: aWorker).
	^ aWorker
]

{ #category : 'accessing' }
CRRuntime >> runners [
	^ runners
]

{ #category : 'lifecycle' }
CRRuntime >> start [
	"I start my runtime and all registered workers. I announce that I started."

	isRunning ifTrue: [ ^ self ].

	isRunning := true.
	self registry register: self.
	self announcer announce: (CRRuntimeStartedAnnouncement runtime: self).

	workers do: [ :w | self ensureRunnerStartedFor: w ]
]

{ #category : 'lifecycle' }
CRRuntime >> stop [
	"I stop all workers and unregister myself. I announce that I stopped."

	isRunning ifFalse: [ ^ self ].

	[ runners valuesDo: [ :runner | runner stop ].
	runners := IdentityDictionary new.
	isRunning := false.
	self announcer announce: (CRRuntimeStoppedAnnouncement runtime: self) ]
		ensure: [ isRunning ifFalse: [ self registry unregister: self ] ]
]

{ #category : 'workers' }
CRRuntime >> workers [
	"I answer my workers."

	^ workers copy
]
