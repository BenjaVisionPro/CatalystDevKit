Class {
	#name : 'CRWorkerTests',
	#superclass : 'CRAbstractWorkerTests',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'examples' }
CRWorkerTests >> example_scaffoldStartsAndStopsWorker [ 
	<gtExample>
	| worker host |
	worker := CRWorker new.
	host := self startWorker: worker andWaitUpToMSecs: 200.

	"Now prove teardown works even if we stop explicitly here."
	host ensureStoppedUpToMSecs: 1000.

	^ Dictionary new
		at: #worker put: worker;
		at: #finalStatus put: worker status;
		yourself
]

{ #category : 'examples' }
CRWorkerTests >> example_stopPreventsNewWorkButDrainsQueue [
	<gtExample>
	^ self
		withRunningWorkerDo: [ :worker :host | 
			| counter rejected |
			counter := 0.
			rejected := false.

			worker enqueue: (self newBlockUnit: [ counter := counter + 1 ]).
			worker enqueue: (self newBlockUnit: [ counter := counter + 1 ]).
			worker enqueue: (self newBlockUnit: [ counter := counter + 1 ]).

			worker stop.

			[ worker enqueue: (self newBlockUnit: [ counter := counter + 1 ]) ]
				on: CRWorkerNotAcceptingWorkException
				do: [ :ex | rejected := true ].

			self
				waitUntil: [ counter = 3 ]
				upToMSecs: 500
				description: 'waiting for already-queued work to drain after stop. status='
						, worker status printString.

			Dictionary new
				at: #counter put: counter;
				at: #rejected put: rejected;
				at: #status put: worker status;
				yourself ]
]

{ #category : 'examples' }
CRWorkerTests >> example_unitRunsExactlyOnce [
	<gtExample>
	^ self
		withRunningWorkerDo: [ :worker :host | 
			| counter |
			counter := 0.

			worker enqueue: (self newBlockUnit: [ counter := counter + 1 ]).

			self
				waitUntil: [ counter = 1 ]
				upToMSecs: 500
				description: 'waiting for unit to run at least once. status='
						, worker status printString.

			self
				assertStaysFalse: [ counter > 1 ]
				upToMSecs: 100
				description: 'unit ran more than once (counter should stay at 1).'.

			Dictionary new
				at: #counter put: counter;
				at: #status put: worker status;
				yourself ]
]

{ #category : 'examples' }
CRWorkerTests >> example_workerAnnouncesFailedWorkUnitAndContinues [ 
	<gtExample>
	^ self withRunningWorkerDo: [ :worker :host |
		| failures counter |
		failures := OrderedCollection new.
		counter := 0.

		worker announcer
			when: CRWorkUnitFailedAnnouncement
			do: [ :ann | failures add: ann ]
			for: self.

		"1) enqueue a unit that fails"
		worker enqueue: (CRBlockUnit on: [ Error signal: 'Intentional test failure.' ]).

		"2) enqueue a unit that must still execute"
		worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

		"Wait for both conditions: failure observed + success ran"
		self
			waitUntil: [ failures notEmpty ]
			upToMSecs: 500
			description: 'waiting for CRWorkUnitFailedAnnouncement to be announced. status=', worker status printString.

		self
			waitUntil: [ counter = 1 ]
			upToMSecs: 500
			description: 'waiting for worker to continue after failure and execute next unit. status=', worker status printString.

		Dictionary new
			at: #failureCount put: failures size;
			at: #counter put: counter;
			at: #status put: worker status;
			yourself
	]
]

{ #category : 'examples' }
CRWorkerTests >> example_workerExecutesAWorkUnit [
	<gtExample>
	^ self
		withRunningWorkerDo: [ :worker :host | 
			| counter |
			counter := 0.

			worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

			self
				waitUntil: [ counter = 1 ]
				upToMSecs: 500
				description: 'waiting for worker to execute enqueued CRBlockUnit (counter should reach 1). status='
						, worker status printString.

			Dictionary new
				at: #counter put: counter;
				at: #status put: worker status;
				yourself ]
]

{ #category : 'examples' }
CRWorkerTests >> example_workerExecutesUnitsInOrder [
	<gtExample>
	^ self
		withRunningWorkerDo: [ :worker :host | 
			| results |
			results := OrderedCollection new.

			worker enqueue: (self newBlockUnit: [ results add: 1 ]).
			worker enqueue: (self newBlockUnit: [ results add: 2 ]).
			worker enqueue: (self newBlockUnit: [ results add: 3 ]).

			self
				waitUntil: [ results size = 3 ]
				upToMSecs: 500
				description: 'waiting for 3 enqueued units to execute (FIFO order). status='
						, worker status printString.

			Dictionary new
				at: #results put: results asArray;
				at: #status put: worker status;
				yourself ]
]

{ #category : 'examples' }
CRWorkerTests >> example_workerRejectsEnqueueWhenStopped [
	<gtExample>
	| worker |
	worker := self newWorker.

	^ [ worker enqueue: (self newBlockUnit: [  ]).
	Dictionary new
		at: #accepted put: true;
		at: #status put: worker status;
		yourself ]
		on: CRWorkerNotAcceptingWorkException
		do: [ :ex | 
			Dictionary new
				at: #accepted put: false;
				at: #exceptionClass put: ex class;
				at: #status put: worker status;
				yourself ]
]

{ #category : 'tests' }
CRWorkerTests >> test_enqueueAfterStopIsRejected [
	self
		withRunningWorkerDo: [ :worker :host | 
			worker stop.
			self
				should: [ worker enqueue: (self newBlockUnit: [  ]) ]
				raise: CRWorkerNotAcceptingWorkException ]
]

{ #category : 'tests' }
CRWorkerTests >> test_enqueueRejectedWhileShuttingDown [
	self
		withRunningWorkerDo: [ :worker :host | 
			worker stop.
			self assert: worker status equals: CRStatus shuttingDown.

			self
				should: [ worker enqueue: (CRBlockUnit on: [  ]) ]
				raise: CRWorkerNotAcceptingWorkException ]
]

{ #category : 'tests' }
CRWorkerTests >> test_example_scaffoldStartsAndStopsWorker [
	| result |
	result := self example_scaffoldStartsAndStopsWorker.
	self assert: (result includesKey: #worker).
	self assert: (result includesKey: #finalStatus)
]

{ #category : 'tests' }
CRWorkerTests >> test_example_stopPreventsNewWorkButDrainsQueue [
	| result |
	result := self example_stopPreventsNewWorkButDrainsQueue.
	self assert: (result at: #rejected).
	self assert: (result at: #counter) equals: 3
]

{ #category : 'tests' }
CRWorkerTests >> test_example_unitRunsExactlyOnce [
	| result |
	result := self example_unitRunsExactlyOnce.
	self assert: (result at: #counter) equals: 1
]

{ #category : 'tests' }
CRWorkerTests >> test_example_workerAnnouncesFailedWorkUnitAndContinues [
	| result |
	result := self example_workerAnnouncesFailedWorkUnitAndContinues.

	self assert: (result at: #failureCount) >= 1.
	self assert: (result at: #counter) equals: 1
]

{ #category : 'tests' }
CRWorkerTests >> test_example_workerExecutesAWorkUnit [
	| result |
	result := self example_workerExecutesAWorkUnit.
	self assert: (result at: #counter) equals: 1
]

{ #category : 'tests' }
CRWorkerTests >> test_example_workerExecutesUnitsInOrder [
	| result |
	result := self example_workerExecutesUnitsInOrder.
	self assert: (result at: #results) equals: #(1 2 3)
]

{ #category : 'tests' }
CRWorkerTests >> test_example_workerRejectsEnqueueWhenStopped [
	| result |
	result := self example_workerRejectsEnqueueWhenStopped.
	self deny: (result at: #accepted).
	self
		assert: (result at: #exceptionClass)
		equals: CRWorkerNotAcceptingWorkException
]

{ #category : 'tests' }
CRWorkerTests >> test_failureAnnouncementEmittedOncePerFailingUnit [
	self
		withRunningWorkerDo: [ :worker :host | 
			| failures |
			failures := OrderedCollection new.

			worker announcer
				when: CRWorkUnitFailedAnnouncement
				do: [ :ann | failures add: ann ]
				for: self.

			worker enqueue: (CRBlockUnit on: [ Error signal: 'fail 1' ]).
			worker enqueue: (CRBlockUnit on: [ Error signal: 'fail 2' ]).

			self
				waitUntil: [ failures size = 2 ]
				upToMSecs: 500
				description: 'waiting for two CRWorkUnitFailedAnnouncement.'.

			self assert: failures size equals: 2 ]
]

{ #category : 'tests' }
CRWorkerTests >> test_scheduledWorkSkipsWhileInFlight_thenResumes [
	| worker host enteredGate releaseGate counter schedule |
	counter := 0.
	enteredGate := Semaphore new.
	releaseGate := Semaphore new.

	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	[ schedule := (CRRepeatingSchedule
			workUnitFactory: [ CRBlockUnit
					on: [ counter := counter + 1.
						enteredGate signal.
						releaseGate wait ] ]
			key: #heartbeat
			intervalMillis: 20)
			scheduledMillis: Time millisecondClockValue;
			yourself.

	worker scheduler addSchedule: schedule.	
	
	"Wait until the first scheduled unit starts running (and blocks)."
	self
		waitUntil: [ enteredGate waitTimeoutMilliseconds: 200 ]
		upToMSecs: 250
		description: 'waiting for first scheduled unit to start'.	
		
	"Give it time to attempt repeats; skip policy should prevent counter incrementing again."
	(Delay forMilliseconds: 80) wait.
	self assert: counter equals: 1.	
	
	"Allow the in-flight unit to finish."
	releaseGate signal.	
	
	"Now we should eventually see a second run."
	self
		waitUntil: [ counter >= 2 ]
		upToMSecs: 500
		description: 'waiting for scheduled unit to run again after completion.'.

	self assert: counter >= 2 ]
		ensure: [ worker stop.
			host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerTests >> test_stopConvergesToStopped [
	| worker host |
	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	[ worker stop.

	self
		waitUntil: [ worker status == CRStatus stopped ]
		upToMSecs: self stopTimeoutMSecs
		description: 'waiting for worker to reach stopped after stop. status='
				, worker status printString.

	self assert: worker status equals: CRStatus stopped ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerTests >> test_stopIsIdempotent [
	| worker host |
	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	[ worker stop.
	worker stop.
	worker stop.

	self
		waitUntil: [ worker status == CRStatus stopped ]
		upToMSecs: self stopTimeoutMSecs
		description: 'waiting for worker to reach stopped after repeated stop requests. status='
				, worker status printString.

	self assert: worker status equals: CRStatus stopped ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerTests >> test_workUnitRunsAtMostOnce [
	self
		withRunningWorkerDo: [ :worker :host | 
			| counter |
			counter := 0.

			worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

			self
				waitUntil: [ counter = 1 ]
				upToMSecs: 500
				description: 'waiting for unit to run once.'.

			self
				assertStaysFalse: [ counter > 1 ]
				upToMSecs: 100
				description: 'unit executed more than once (regression guard).' ]
]

{ #category : 'tests' }
CRWorkerTests >> test_workerBecomesRunningAndAcceptsWork [
	self
		withRunningWorkerDo: [ :worker :host | 
			self
				assert: worker isAcceptingWork
				description: 'Expected worker to be accepting work while running.' ]
]

{ #category : 'tests' }
CRWorkerTests >> test_workerExecutesAWorkUnit [
	| worker host counter |
	counter := 0.
	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	[ worker enqueue: (CRBlockUnit on: [ counter := counter + 1 ]).

	self
		waitUntil: [ counter = 1 ]
		upToMSecs: 500
		description: 'waiting for worker to execute enqueued CRBlockUnit. status='
				, worker status printString.

	self assert: counter equals: 1 ]
		ensure: [ worker stop.
			host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerTests >> test_workerExecutesScheduledWorkUnit_atLeastOnce [
	| worker host schedule counter |
	counter := 0.
	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	[ schedule := (CRRepeatingSchedule
			workUnitFactory: [ CRBlockUnit on: [ counter := counter + 1 ] ]
			key: #heartbeat
			intervalMillis: 20)
			scheduledMillis: Time millisecondClockValue;
			yourself.

	worker scheduler addSchedule: schedule.

	self
		waitUntil: [ counter >= 1 ]
		upToMSecs: 500
		description: 'waiting for scheduled heartbeat unit to execute at least once. status='
				, worker status printString.

	self assert: counter >= 1 ]
		ensure: [ worker stop.
			host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]
