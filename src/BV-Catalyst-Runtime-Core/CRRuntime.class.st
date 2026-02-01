Class {
	#name : 'CRRuntime',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'workers',
		'runners',
		'announcer',
		'status',
		'configuration',
		'orchestratorWorker',
		'orchestratorRunner'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'orchestration' }
CRRuntime class >> orchestratorIdentifier [
	^ #runtimeOrchestrator
]

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

{ #category : 'configuration' }
CRRuntime >> applyConfiguration: aCRRuntimeConfiguration [
	| validation orchCfg runningOrchClass |
	validation := aCRRuntimeConfiguration validate.
	validation isValid
		ifFalse: [ CRInvalidRuntimeConfigurationException
				configuration: aCRRuntimeConfiguration
				validationResult: validation ].

	configuration := aCRRuntimeConfiguration.

	self hasRunningOrchestrator not
		ifTrue: [ self bootstrapOrchestratorFrom: aCRRuntimeConfiguration ].

	orchCfg := aCRRuntimeConfiguration
			workerConfigurationNamed: self class orchestratorIdentifier.

	runningOrchClass := orchestratorWorker workerClass.
	runningOrchClass = orchCfg workerClass
		ifFalse: [ CRRuntimeOrchestratorClassMismatchException
				currentClass: runningOrchClass
				requestedClass: orchCfg workerClass ].

	self enqueueApplyConfigurationUnit: aCRRuntimeConfiguration
]

{ #category : 'configuration' }
CRRuntime >> applyConfigurationFromFile: aPath [
	| cfg |
	cfg := aPath asFileReference
			readStreamDo: [ :stream | STON fromStream: stream ].

	self applyConfiguration: cfg
]

{ #category : 'workers' }
CRRuntime >> bootstrapOrchestratorFrom: aCRRuntimeConfiguration [
	| orchCfg |
	orchCfg := aCRRuntimeConfiguration
			workerConfigurationNamed: self class orchestratorIdentifier.

	orchestratorWorker := self realiseWorkerFromConfiguration: orchCfg.

	orchestratorRunner := CRWorkerRunner onWorker: orchestratorWorker.
	orchestratorRunner start.

	self waitForWorkerStarted: orchestratorWorker
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

{ #category : 'testing' }
CRRuntime >> hasRunningOrchestrator [
	^ orchestratorWorker notNil
		and: [ orchestratorWorker status == CRStatus running ]
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

{ #category : 'testing' }
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
