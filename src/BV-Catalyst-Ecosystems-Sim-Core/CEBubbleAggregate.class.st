Class {
	#name : 'CEBubbleAggregate',
	#superclass : 'CESimAggregate',
	#instVars : [
		'commandQueue',
		'visibleEntityIds',
		'homeRegionId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CEBubbleAggregate class >> withId: aBubbleId homeRegionId: aRegionId [
	^ (self withId: aBubbleId)
		withHomeRegionId: aRegionId;
		yourself
]

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

{ #category : 'accessing' }
CEBubbleAggregate >> homeRegionId [
	^ homeRegionId
]

{ #category : 'initialization' }
CEBubbleAggregate >> initialize [
	super initialize.
	commandQueue := OrderedCollection new.
	visibleEntityIds := OrderedCollection new
]

{ #category : 'accessing' }
CEBubbleAggregate >> moveToHomeRegionId: aRegionId [
	homeRegionId := aRegionId
]

{ #category : 'commands' }
CEBubbleAggregate >> pendingCommandsCount [
	^ commandQueue size
]

{ #category : 'regions' }
CEBubbleAggregate >> relevantRegionIds [
	"v0: only home region. Later: include micro-bubble region ids / halo overlaps."

	homeRegionId ifNil: [ ^ #() ].
	^ {homeRegionId}
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

{ #category : 'accessing' }
CEBubbleAggregate >> withHomeRegionId: aRegionId [
	homeRegionId := aRegionId
]
