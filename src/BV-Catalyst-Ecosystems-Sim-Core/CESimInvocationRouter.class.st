Class {
	#name : 'CESimInvocationRouter',
	#superclass : 'Object',
	#instVars : [
		'entityDirectory',
		'partitionMap'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInvocationRouter class >> entityDirectory: anEntityDirectory partitionMap: aPartitionMap [
	"I create a router that can address invocations to partition ids using the supplied directory and partition map."

	^ self new
		entityDirectory: anEntityDirectory;
		partitionMap: aPartitionMap;
		yourself
]

{ #category : 'accessing' }
CESimInvocationRouter >> entityDirectory: anObject [
	entityDirectory := anObject
]

{ #category : 'routing' }
CESimInvocationRouter >> partitionIdsForInvocation: anInvocation inContext: aContext [
	"I ask the invocation to define how it should be routed using me."

	^ anInvocation routeOn: self inContext: aContext
]

{ #category : 'routing' }
CESimInvocationRouter >> partitionIdsForTargetEntityId: anEntityId inContext: aContext [
	"I answer the partition id(s) that own the target entity id.
	TODO: When routing must respect playerIntentTickId via historical ownership, incorporate that tick into the lookup."

	| partitionId |
	partitionId := entityDirectory
			partitionIdForEntityId: anEntityId
			inEngine: aContext engine
			ifAbsent: [ ^ #() ].

	^ {partitionId}
]

{ #category : 'routing' }
CESimInvocationRouter >> partitionIdsForTransform: aTransform inContext: aContext [
	"I answer the partition id(s) that cover this transform, in deterministic order."

	| partitionIds |
	partitionIds := partitionMap
			partitionIdsForTransform: aTransform
			inContext: aContext.

	^ (partitionIds asSortedCollection: [ :a :b | a < b ]) asArray
]

{ #category : 'accessing' }
CESimInvocationRouter >> partitionMap: anObject [
	partitionMap := anObject
]

{ #category : 'routing' }
CESimInvocationRouter >> route: anEnvelope inContext: aContext [
	"I deliver an invocation envelope to the partition inboxes that should receive it."

	| partitionIds |
	partitionIds := self
			partitionIdsForInvocation: anEnvelope invocation
			inContext: aContext.

	partitionIds
		do: [ :partitionId | 
			(aContext engine ensurePartition: partitionId)
				enqueueInvocationEnvelope: anEnvelope ]
]
