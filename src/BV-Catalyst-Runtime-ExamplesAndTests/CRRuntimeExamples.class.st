Class {
	#name : 'CRRuntimeExamples',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'examples' }
CRRuntimeExamples >> example_runtimeStartStop [
	<gtExample>
	| seed runtime |
	seed := self example_runtimeWithOneWorker.
	runtime := seed at: #runtime.

	runtime start.
	runtime stop.

	^ Dictionary new
		at: #runtime put: runtime;
		yourself
]

{ #category : 'examples' }
CRRuntimeExamples >> example_runtimeWithOneWorker [
	<gtExample>
	| runtime worker |
	runtime := CRRuntime new.
	worker := CRWorker new
			displayName: 'Worker-1';
			yourself.
	runtime addWorker: worker.

	^ Dictionary new
		at: #runtime put: runtime;
		at: #worker put: worker;
		yourself
]

{ #category : 'examples' }
CRRuntimeExamples >> example_workerRunsAWorkUnit_runOnce [
	<gtExample>
	| seed worker runner ran counter |
	seed := self example_runtimeWithOneWorker.
	worker := seed at: #worker.

	runner := CRInlineWorkerRunner on: worker.
	runner start.

	counter := 0.
	worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

	ran := runner runOnce.

	runner stop.

	^ Dictionary new
		at: #worker put: worker;
		at: #runner put: runner;
		at: #ran put: ran;
		at: #counter put: counter;
		yourself
]

{ #category : 'tests' }
CRRuntimeExamples >> test_announcerOperationsChannel_canBeDisabled [
	| runtime events |
	runtime := CRRuntime new.

	events := OrderedCollection new.
	runtime announcer
		when: CRRuntimeAnnouncement
		do: [ :ann | events add: ann ]
		for: self.

	runtime announcer disableChannel: CRAnnouncer operationsChannel.

	runtime start.
	runtime stop.

	self assert: events isEmpty
]

{ #category : 'tests' }
CRRuntimeExamples >> test_basicEnqueueStillWorksDuringShutdown [
	| worker |
	worker := CRWorker new.
	worker requestGracefulStop.	"Should not raise"
	worker basicEnqueue: CRWakeupWorkUnit new
]

{ #category : 'tests' }
CRRuntimeExamples >> test_enqueueSignalsNotAcceptingWork [
	| worker |
	worker := CRWorker new.
	worker requestGracefulStop.

	self
		should: [ worker enqueue: (CRBlockUnit on: [ 1 ]) ]
		raise: CRWorkerNotAcceptingWorkException
]

{ #category : 'tests' }
CRRuntimeExamples >> test_example_runtimeStartStop_registersAndUnregisters [
	| runtime |
	runtime := (self example_runtimeStartStop) at: #runtime.

	self assert: (CRRuntimeRegistry default runtimes includes: runtime) equals: false
]

{ #category : 'tests' }
CRRuntimeExamples >> test_example_workerRunsAWorkUnit_runOnce_executes [
	| seed ran counter |
	seed := self example_workerRunsAWorkUnit_runOnce.
	ran := seed at: #ran.
	counter := seed at: #counter.

	self assert: ran equals: true.
	self assert: counter equals: 1
]

{ #category : 'tests' }
CRRuntimeExamples >> test_exceptionCarriesWorkerAndUnit [
	| worker unit |
	worker := CRWorker new.
	unit := CRBlockUnit on: [ 1 ].
	worker requestGracefulStop.

	self
		should: [ worker enqueue: unit ]
		raise: CRWorkerNotAcceptingWorkException
		withExceptionDo: [ :ex | 
			self assert: ex worker == worker.
			self assert: ex unit == unit.
			self assert: ex reason notNil ]
]

{ #category : 'tests' }
CRRuntimeExamples >> test_runtimeStartStop_emitsAnnouncements [
	| runtime events |
	runtime := CRRuntime new.

	events := OrderedCollection new.
	runtime announcer
		when: CRRuntimeAnnouncement
		do: [ :ann | events add: ann ]
		for: self.

	runtime start.
	runtime stop.

	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeStartingUpAnnouncement ]).
	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeStartedAnnouncement ]).
	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeShuttingDownAnnouncement ]).
	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeStoppedAnnouncement ])
]

{ #category : 'tests' }
CRRuntimeExamples >> test_runtimeWorkerAddRemove_emitsAnnouncements [
	| runtime worker events |
	runtime := CRRuntime new.
	worker := CRWorker new.

	events := OrderedCollection new.
	runtime announcer
		when: CRRuntimeWorkerAnnouncement
		do: [ :ann | events add: ann ]
		for: self.

	runtime addWorker: worker.
	runtime removeWorker: worker.

	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeWorkerAddedAnnouncement ]).
	self
		assert: (events anySatisfy: [ :e | e class = CRRuntimeWorkerRemovedAnnouncement ])
]

{ #category : 'tests' }
CRRuntimeExamples >> test_workerDoesNotAcceptWorkUnlessRunning [
	| worker |
	worker := CRWorker new.

	self
		should: [ worker enqueue: (CRBlockUnit on: [ 1 ]) ]
		raise: CRWorkerNotAcceptingWorkException
]

{ #category : 'tests' }
CRRuntimeExamples >> test_workerDoesNotAcceptWorkWhileShuttingDown [
	| worker runner |
	worker := CRWorker new.
	runner := CRInlineWorkerRunner on: worker.
	runner start.

	worker requestGracefulStop.

	self
		should: [ worker enqueue: (CRBlockUnit on: [ 1 ]) ]
		raise: CRWorkerNotAcceptingWorkException.

	runner stop
]

{ #category : 'tests' }
CRRuntimeExamples >> test_workerRunsAWorkUnit_runOnce [
	| seed worker runner ran counter |
	seed := self example_runtimeWithOneWorker.
	worker := seed at: #worker.

	runner := CRInlineWorkerRunner on: worker.
	runner start.

	counter := 0.
	worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

	ran := runner runOnce.

	self assert: ran.
	self assert: counter equals: 1.

	runner stop
]
