Class {
	#name : 'CERegionAggregate',
	#superclass : 'CESimAggregate',
	#instVars : [
		'entitiesById'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'notables' }
CERegionAggregate >> addEntity: aCEEntity [
	entitiesById at: aCEEntity entityId put: aCEEntity
]

{ #category : 'notables' }
CERegionAggregate >> entities [
	"Deterministic ordering: by entityId backing value."

	^ (entitiesById values
		asSortedCollection: [ :a :b | a entityId value < b entityId value ])
		asOrderedCollection
]

{ #category : 'notables' }
CERegionAggregate >> entityAt: aCEEntityId [
	^ self entityAt: aCEEntityId ifAbsent: [ nil ]
]

{ #category : 'notables' }
CERegionAggregate >> entityAt: aCEEntityId ifAbsent: aBlock [
    ^ entitiesById at: aCEEntityId ifAbsent: aBlock
]

{ #category : 'initialization' }
CERegionAggregate >> initialize [
	super initialize.
	entitiesById := Dictionary new
]

{ #category : 'accessing' }
CERegionAggregate >> regionId [
	^ self aggregateId
]

{ #category : 'notables' }
CERegionAggregate >> removeEntityId: aCEEntityId [
    entitiesById removeKey: aCEEntityId ifAbsent: [ ].
]
