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
CRWorkerTests >> example_workerExecutesAWorkUnit [
	<gtExample>
	^ self
		withRunningWorkerDo: [ :worker | 
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

{ #category : 'tests' }
CRWorkerTests >> test_example_workerExecutesAWorkUnit [
	| result |
	result := self example_workerExecutesAWorkUnit.
	self assert: (result at: #counter) equals: 1
]
