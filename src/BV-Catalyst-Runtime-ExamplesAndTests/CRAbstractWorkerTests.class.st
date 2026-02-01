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
CRAbstractWorkerTests >> assertStaysFalse: aZeroArgBooleanBlock upToMSecs: timeoutMSecs description: aString [
	| startTime |
	startTime := Time millisecondClockValue.

	[ Time millisecondClockValue - startTime < timeoutMSecs ]
		whileTrue: [ aZeroArgBooleanBlock value
				ifTrue: [ self error: 'Became true unexpectedly: ' , aString ].
			(Delay forMilliseconds: 1) wait ]
]

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

{ #category : 'factory' }
CRAbstractWorkerTests >> newBlockUnit: aBlock [
	^ CRBlockUnit on: aBlock
]

{ #category : 'factory' }
CRAbstractWorkerTests >> newWorker [
	^ CRWorker new
]

{ #category : 'running' }
CRAbstractWorkerTests >> setUp [
	super setUp.
	self initializeHosts.
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> startTimeoutMSecs [
	^ 200
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> startWorker: aWorker andWaitUpToMSecs: timeoutMSecs [
	| host |
	host := self hostWorker: aWorker.
	host start.
	host waitUntilRunningUpToMSecs: timeoutMSecs.
	^ host
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> stopTimeoutMSecs [
	^ 2000
]

{ #category : 'running' }
CRAbstractWorkerTests >> tearDown [
	"Hard guarantee: no worker processes survive a test."

	hosts
		ifNotNil: [ hosts
				do: [ :each | 
					[ each ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
						on: Error
						do: [  "Swallow during teardown to avoid masking failures":ex |  ] ] ].

	super tearDown
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> waitUntil: aZeroArgBooleanBlock upToMSecs: timeoutMSecs description: aString [
	| startTime |
	startTime := Time millisecondClockValue.

	[ aZeroArgBooleanBlock value
		or: [ Time millisecondClockValue - startTime >= timeoutMSecs ] ]
		whileFalse: [ (Delay forMilliseconds: 1) wait ].

	aZeroArgBooleanBlock value ifFalse: [ self error: 'Timed out: ' , aString ]
]

{ #category : 'helpers' }
CRAbstractWorkerTests >> withRunningWorkerDo: aTwoArgBlock [
	"Convenience wrapper: always stops even if the block fails."

	| worker host |
	worker := self newWorker.
	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.

	^ [ aTwoArgBlock value: worker value: host ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]
