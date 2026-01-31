Class {
	#name : 'CRAbstractWorkerTests',
	#superclass : 'TestCase',
	#instVars : [
		'hosts'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'helpers' }
CRAbstractWorkerTests >> hostWorker: aWorker [
	| host |
	host := CRWorkerTestHost onWorker: aWorker.
	hosts add: host.
	^ host
]

{ #category : 'as yet unclassified' }
CRAbstractWorkerTests >> initialize [
	super initialize.
	self initializeHosts
]

{ #category : 'running' }
CRAbstractWorkerTests >> initializeHosts [
	hosts := OrderedCollection new
]

{ #category : 'running' }
CRAbstractWorkerTests >> setUp [
	super setUp.
	self initializeHosts.
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> startWorker: aWorker andWaitUpToMSecs: timeoutMSecs [
	| host |
	host := self hostWorker: aWorker.
	host
		start;
		waitUntilRunningUpToMSecs: timeoutMSecs.
	^ host
]

{ #category : 'running' }
CRAbstractWorkerTests >> tearDown [
	"Hard guarantee: no worker processes survive a test."

	hosts
		ifNotNil: [ hosts
				do: [ :each | 
					[ each ensureStoppedUpToMSecs: 2000 ]
						on: Error
						do: [ :ex "swallow during teardown" |  ] ] ].

	hosts := nil.
	super tearDown
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> withRunningWorkerDo: aBlock [
	"Convenience: always stops even if the block errors."
	| worker host |
	worker := CRWorker new.
	host := self startWorker: worker andWaitUpToMSecs: 200.

	^ [ aBlock value: worker ]
		ensure: [ host ensureStoppedUpToMSecs: 2000 ]
]
