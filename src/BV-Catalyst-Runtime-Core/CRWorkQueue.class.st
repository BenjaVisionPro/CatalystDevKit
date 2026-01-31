Class {
	#name : 'CRWorkQueue',
	#superclass : 'Object',
	#instVars : [
		'sharedQueue'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'queue' }
CRWorkQueue >> enqueue: aWorkUnitEnvelope [
	sharedQueue nextPut: aWorkUnitEnvelope.
	^ aWorkUnitEnvelope
]

{ #category : 'initialization' }
CRWorkQueue >> initialize [
	"I initialise my queue."

	super initialize.
	sharedQueue := SharedQueue new
]

{ #category : 'queue' }
CRWorkQueue >> next: timeoutMillis ifNone: aFallbackEnvelope [
	"Non-blocking wait: repeatedly poll nextOrNil and yield.
	Returns fallback if no work arrives before timeoutMillis."

	| startMillis envelope nowMillis |
	timeoutMillis <= 0 ifTrue: [ ^ self nextOrNil ifNil: [ aFallbackEnvelope ] ].

	startMillis := Time millisecondClockValue.

	[ envelope := self nextOrNil.
	envelope ifNotNil: [ ^ envelope ].

	nowMillis := Time millisecondClockValue.
	nowMillis - startMillis >= timeoutMillis ifTrue: [ ^ aFallbackEnvelope ].

	Processor yield.
	false ] whileFalse
]

{ #category : 'queue' }
CRWorkQueue >> nextOrNil [
	"I answer the next work item if one is available, otherwise nil."

	^ sharedQueue nextOrNil
]
