Class {
	#name : 'CESimPartition',
	#superclass : 'CESimAggregate',
	#instVars : [
		'entitiesById'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'notables' }
CESimPartition >> addEntity: anEntity [
	entitiesById at: anEntity entityId put: anEntity
]

{ #category : 'notables' }
CESimPartition >> entities [
	"Deterministic ordering: by entityId backing value."

	^ (entitiesById values
		asSortedCollection: [ :a :b | a entityId value < b entityId value ])
		asOrderedCollection
]

{ #category : 'notables' }
CESimPartition >> entityAt: anEntityId [
	^ self entityAt: anEntityId ifAbsent: [ nil ]
]

{ #category : 'notables' }
CESimPartition >> entityAt: anEntityId ifAbsent: aBlock [
    ^ entitiesById at: anEntityId ifAbsent: aBlock
]

{ #category : 'notables' }
CESimPartition >> includesEntityId: anEntityId [
	^ entitiesById includesKey: anEntityId
]

{ #category : 'initialization' }
CESimPartition >> initialize [
	super initialize.
	entitiesById := Dictionary new
]

{ #category : 'as yet unclassified' }
CESimPartition >> partitionId [
	^ aggregateId
]

{ #category : 'notables' }
CESimPartition >> removeEntityId: anEntityId [
	entitiesById removeKey: anEntityId ifAbsent: [  ]
]
