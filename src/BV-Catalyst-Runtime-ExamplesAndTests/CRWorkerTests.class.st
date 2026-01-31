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
	host ensureStoppedUpToMSecs: 2000.

	^ Dictionary new
		at: #worker put: worker;
		at: #finalStatus put: worker status;
		yourself
]
