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
CESimPartition >> addEntity: aCEEntity [
	entitiesById at: aCEEntity entityId put: aCEEntity
]

{ #category : 'notables' }
CESimPartition >> entities [
	"Deterministic ordering: by entityId backing value."

	^ (entitiesById values
		asSortedCollection: [ :a :b | a entityId value < b entityId value ])
		asOrderedCollection
]

{ #category : 'notables' }
CESimPartition >> entityAt: aCEEntityId [
	^ self entityAt: aCEEntityId ifAbsent: [ nil ]
]

{ #category : 'notables' }
CESimPartition >> entityAt: aCEEntityId ifAbsent: aBlock [
    ^ entitiesById at: aCEEntityId ifAbsent: aBlock
]

{ #category : 'initialization' }
CESimPartition >> initialize [
	super initialize.
	entitiesById := Dictionary new
]

{ #category : 'accessing' }
CESimPartition >> regionId [
	^ self aggregateId
]

{ #category : 'notables' }
CESimPartition >> removeEntityId: aCEEntityId [
    entitiesById removeKey: aCEEntityId ifAbsent: [ ].
]
