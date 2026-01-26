Class {
	#name : 'CEBubbleAggregate',
	#superclass : 'CESimAggregate',
	#instVars : [
		'commandQueue',
		'ownerEntityId',
		'partitionId',
		'collectedEntityIds'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CEBubbleAggregate class >> withId: aBubbleId partitionId: aPartitionId [
	^ (self withId: aBubbleId)
		partitionId: aPartitionId;
		yourself
]

{ #category : 'accessing' }
CEBubbleAggregate >> bubbleId [
	^ self aggregateId
]

{ #category : 'visibility' }
CEBubbleAggregate >> collectedEntityIds [
	^ collectedEntityIds copy
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
CEBubbleAggregate >> initialize [
	super initialize.
	commandQueue := OrderedCollection new.
	collectedEntityIds := OrderedCollection new
]

{ #category : 'accessing' }
CEBubbleAggregate >> moveToPartitionId: aPartitionId [
	partitionId := aPartitionId
]

{ #category : 'accessing' }
CEBubbleAggregate >> ownerEntityId [
	^ ownerEntityId
]

{ #category : 'accessing' }
CEBubbleAggregate >> partitionId [
	^ partitionId
]

{ #category : 'accessing' }
CEBubbleAggregate >> partitionId: aPartitionId [
	partitionId := aPartitionId
]

{ #category : 'partitions' }
CEBubbleAggregate >> partitionIdsForSnapshotCollection [
	"I point at the partition that holds my entities."

	^ {self partitionId}
]

{ #category : 'visibility' }
CEBubbleAggregate >> setCollectedEntityIds: aCollection [
	"Store in deterministic order (by id value)."

	collectedEntityIds := (aCollection asOrderedCollection
			asSortedCollection: [ :a :b | a value < b value ]) asOrderedCollection
]
