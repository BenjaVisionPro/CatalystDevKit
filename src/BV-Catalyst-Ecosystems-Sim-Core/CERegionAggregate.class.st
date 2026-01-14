Class {
	#name : 'CERegionAggregate',
	#superclass : 'CESimAggregate',
	#instVars : [
		'notablesById'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'notables' }
CERegionAggregate >> addNotable: aCENotable [
	notablesById at: aCENotable entityId put: aCENotable
]

{ #category : 'initialization' }
CERegionAggregate >> initializeWithId: aCERegionId [
	super initializeWithId: aCERegionId.
	notablesById := Dictionary new
]

{ #category : 'notables' }
CERegionAggregate >> notableAt: aCEEntityId ifAbsent: aBlock [
    ^ notablesById at: aCEEntityId ifAbsent: aBlock
]

{ #category : 'notables' }
CERegionAggregate >> notables [
	"Deterministic ordering: by entityId backing value."

	^ (notablesById values
		asSortedCollection: [ :a :b | a entityId value < b entityId value ])
		asOrderedCollection
]

{ #category : 'accessing' }
CERegionAggregate >> regionId [
	^ self aggregateId
]

{ #category : 'notables' }
CERegionAggregate >> removeNotableId: aCEEntityId [
    notablesById removeKey: aCEEntityId ifAbsent: [ ].
]
