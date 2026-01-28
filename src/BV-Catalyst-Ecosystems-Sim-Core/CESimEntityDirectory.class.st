Class {
	#name : 'CESimEntityDirectory',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimEntityDirectory >> partitionIdForEntityId: anEntityId inEngine: anEngine ifAbsent: aBlock [
	"I answer the current owning partition id for an entity id."

	| partition |
	partition := anEngine
			partitionContainingEntityId: anEntityId
			ifNone: [ ^ aBlock value ].

	^ partition partitionId
]
