Class {
	#name : 'CRRuntime',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workers',
		'runners',
		'announcer',
		'status'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'workers' }
CRRuntime >> addWorker: aWorker [
	workers add: aWorker.
	self announcer
		announce: (CRRuntimeWorkerAddedAnnouncement runtime: self worker: aWorker).

	status == CRStatus running ifTrue: [ self ensureRunnerStartedFor: aWorker ].
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

	^ CRWorkerRunner worker: aWorker
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
	status := CRStatus stopped
]

{ #category : 'as yet unclassified' }
CRRuntime >> isRunning [
	"Compatibility predicate. Truth comes from #status."

	^ status == CRStatus running
]

{ #category : 'private' }
CRRuntime >> registry [
	"I answer the registry used for tracking runtimes (dev/GT)."

	^ CRRuntimeRegistry default
]

{ #category : 'workers' }
CRRuntime >> removeWorker: aWorker [
	(runners at: aWorker ifAbsent: [ nil ])
		ifNotNil: [  "Hard protocol: runner MUST understand stopGraceful":runner | 
			runner stopGraceful.
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
CRRuntime >> shutdownGraceful [
	(status == CRStatus stopped or: [ status == CRStatus shuttingDown ])
		ifTrue: [ ^ self ].

	status := CRStatus shuttingDown.
	self announcer announce: (CRRuntimeShuttingDownAnnouncement runtime: self).

	[ runners valuesDo: [ :runner | runner stopGraceful ].
	runners := IdentityDictionary new.
	status := CRStatus stopped.
	self announcer announce: (CRRuntimeStoppedAnnouncement runtime: self) ]
		ensure: [ status == CRStatus stopped ifTrue: [ self registry unregister: self ] ]
]

{ #category : 'lifecycle' }
CRRuntime >> shutdownImmediate [
	(status == CRStatus stopped or: [ status == CRStatus shuttingDown ])
		ifTrue: [ ^ self ].

	status := CRStatus shuttingDown.
	self announcer announce: (CRRuntimeShuttingDownAnnouncement runtime: self).

	[ runners valuesDo: [ :runner | runner stopImmediate ].
	runners := IdentityDictionary new.
	status := CRStatus stopped.
	self announcer announce: (CRRuntimeStoppedAnnouncement runtime: self) ]
		ensure: [ status == CRStatus stopped ifTrue: [ self registry unregister: self ] ]
]

{ #category : 'lifecycle' }
CRRuntime >> start [ 
	status ~= CRStatus stopped ifTrue: [ ^ self ].

	status := CRStatus startingUp.
	self announcer announce: (CRRuntimeStartingUpAnnouncement runtime: self).

	self registry register: self.

	workers do: [ :w | self ensureRunnerStartedFor: w ].

	status := CRStatus running.
	self announcer announce: (CRRuntimeStartedAnnouncement runtime: self)
]

{ #category : 'accessing' }
CRRuntime >> status [
	^ status
]

{ #category : 'lifecycle' }
CRRuntime >> stop [
	self shutdownGraceful
]

{ #category : 'workers' }
CRRuntime >> workers [
	"I answer my workers."

	^ workers copy
]
