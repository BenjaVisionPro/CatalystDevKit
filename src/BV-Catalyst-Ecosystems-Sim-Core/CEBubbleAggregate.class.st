Class {
	#name : 'CEBubbleAggregate',
	#superclass : 'CESimAggregate',
	#instVars : [
		'commandQueue',
		'visibleEntityIds'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CEBubbleAggregate >> bubbleId [
	^ self aggregateId
]

{ #category : 'commands' }
CEBubbleAggregate >> drainCommands [
	"Remove and answer all currently queued commands, preserving order."

	| drained |
	drained := commandQueue copy.
	commandQueue removeAll.
	^ drained
]

{ #category : 'commands' }
CEBubbleAggregate >> enqueueCommand: aCommand [
	"Commands are stored in arrival order for determinism."

	commandQueue add: aCommand
]

{ #category : 'initialization' }
CEBubbleAggregate >> initializeWithId: aCEBubbleId [
    super initializeWithId: aCEBubbleId.
    commandQueue := OrderedCollection new.
    visibleEntityIds := OrderedCollection new.
]

{ #category : 'commands' }
CEBubbleAggregate >> pendingCommandsCount [
	^ commandQueue size
]

{ #category : 'visibility' }
CEBubbleAggregate >> setVisibleEntityIds: aCollection [
	"Store in deterministic order (by id value)."

	visibleEntityIds := (aCollection asOrderedCollection
			asSortedCollection: [ :a :b | a value < b value ]) asOrderedCollection
]

{ #category : 'visibility' }
CEBubbleAggregate >> visibleEntityIds [
	^ visibleEntityIds copy
]
