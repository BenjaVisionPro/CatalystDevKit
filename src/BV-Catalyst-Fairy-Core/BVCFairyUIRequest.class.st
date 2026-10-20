"
One bounded wait over an existing Bloc universe queue. Queued work can be abandoned; started work remains indexed by its owning chat until it actually finishes. The registry contains at most 64 outstanding requests. No dispatcher, automatic replay or process termination.
"
Class {
	#name : 'BVCFairyUIRequest',
	#superclass : 'Object',
	#instVars : [
		'action',
		'callback',
		'universe',
		'completion',
		'lock',
		'state',
		'result',
		'failure',
		'chat'
	],
	#classInstVars : [
		'requests',
		'registryLock'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'execution' }
BVCFairyUIRequest class >> abandonQueuedForChat: aChat [
	self pending do: [ :request | request chat == aChat ifTrue: [ request abandonIfQueued ] ]
]

{ #category : 'creation' }
BVCFairyUIRequest class >> action: aBlock on: aUniverse [
	^ self new action: aBlock; submitOn: aUniverse; yourself
]

{ #category : 'testing' }
BVCFairyUIRequest class >> hasPendingForChat: aChat [
	^ self pending anySatisfy: [ :request | request chat == aChat ]
]

{ #category : 'accessing' }
BVCFairyUIRequest class >> pending [
	^ self registryLock critical: [ (requests ifNil: [ requests := OrderedCollection new ]) copy ]
]

{ #category : 'private' }
BVCFairyUIRequest class >> register: aRequest [
	self registryLock critical: [
		requests ifNil: [ requests := OrderedCollection new ].
		requests size >= 64 ifTrue: [ self error: 'Too many outstanding Barry UI requests.' ].
		requests add: aRequest ]
]

{ #category : 'private' }
BVCFairyUIRequest class >> registryLock [
	^ registryLock ifNil: [ registryLock := Semaphore forMutualExclusion ]
]

{ #category : 'private' }
BVCFairyUIRequest class >> remove: aRequest [
	self registryLock critical: [
		requests ifNotNil: [ requests remove: aRequest ifAbsent: [ ] ] ]
]

{ #category : 'execution' }
BVCFairyUIRequest class >> value: aBlock on: aUniverse withinMilliseconds: milliseconds [
	| isUIProcess |
	isUIProcess := false.
	(aUniverse isKindOf: BlParallelUniverse)
		ifTrue: [ aUniverse uiProcessDo: [ :process | isUIProcess := Processor activeProcess effectiveProcess == process ] ]
		ifFalse: [ isUIProcess := aUniverse isUIProcess ].
	isUIProcess ifTrue: [ ^ aBlock value ].
	^ (self action: aBlock on: aUniverse) valueWithinMilliseconds: milliseconds
]

{ #category : 'execution' }
BVCFairyUIRequest >> abandonIfQueued [
	| abandoned |
	abandoned := lock critical: [
		state = #queued
			ifTrue: [ state := #abandoned. action := nil.
				failure := Error new messageText: 'Barry UI request abandoned before starting.'. true ]
			ifFalse: [ false ] ].
	abandoned ifTrue: [
		(universe notNil and: [ universe respondsTo: #undefer: ]) ifTrue: [ universe undefer: callback ].
		self class remove: self.
		completion signal ].
	^ abandoned
]

{ #category : 'accessing' }
BVCFairyUIRequest >> action: aBlock [
	action := aBlock
]

{ #category : 'accessing' }
BVCFairyUIRequest >> chat [
	^ chat
]

{ #category : 'accessing' }
BVCFairyUIRequest >> chat: aChat [
	chat := aChat
]

{ #category : 'initialization' }
BVCFairyUIRequest >> initialize [
	super initialize.
	completion := Semaphore new.
	lock := Semaphore forMutualExclusion.
	state := #queued.
	chat := (Processor activeProcess suspendedContext ifNil: [ thisContext ]) stack
		detect: [ :context | context receiver isKindOf: GtLProvider ]
		ifFound: [ :context | context receiver chat ]
		ifNone: [ nil ]
]

{ #category : 'execution' }
BVCFairyUIRequest >> run [
	(chat notNil and: [ chat state = GtLProviderState stopping ]) ifTrue: [
		self abandonIfQueued. ^ self ].
	(lock critical: [
		state = #queued ifFalse: [ false ] ifTrue: [ state := #running. true ] ])
		ifFalse: [ ^ self ].
	[
		[ result := action value ] on: Error do: [ :error | failure := error freeze ]
	] ensure: [
		lock critical: [ state := #finished. action := nil ].
		self class remove: self.
		completion signal ]
]

{ #category : 'accessing' }
BVCFairyUIRequest >> state [
	^ lock critical: [ state ]
]

{ #category : 'execution' }
BVCFairyUIRequest >> submitOn: aUniverse [
	universe := aUniverse.
	callback := [ self run ].
	self class register: self.
	[ universe defer: callback ] on: Error do: [ :error |
		self abandonIfQueued.
		error pass ]
]

{ #category : 'execution' }
BVCFairyUIRequest >> valueWithinMilliseconds: milliseconds [
	| timedOut currentState |
	(milliseconds isInteger and: [ milliseconds between: 1 and: 10000 ])
		ifFalse: [ self error: 'UI wait must be between 1 and 10000 milliseconds.' ].
	[ timedOut := completion waitTimeoutMilliseconds: milliseconds ]
		ifCurtailed: [ self abandonIfQueued ].
	timedOut ifTrue: [
		self abandonIfQueued.
		currentState := self state.
		currentState = #finished ifFalse: [
			self error: (currentState = #abandoned
				ifTrue: [ 'Barry UI request timed out before starting; callback abandoned.' ]
				ifFalse: [ 'Barry UI request timed out after starting; UI work is still outstanding.' ]) ] ].
	failure ifNotNil: [ failure signal ].
	^ result
]
