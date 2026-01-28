Class {
	#name : 'CESimPartitionMap',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimPartitionMap >> partitionIdsForTransform: aTransform inContext: aContext [
	"I answer the partition id(s) that cover this transform.
	TODO: Replace this placeholder with the real spatial mapping implementation."

	| partitions |
	partitions := aContext engine partitions.

	partitions isEmpty ifTrue: [ ^ {aContext engine newPartition partitionId} ].

	^ {partitions first partitionId}
]
