Class {
	#name : 'CESimAddOp',
	#superclass : 'CESimLifecycleOp',
	#instVars : [
		'entity'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimAddOp class >> entity: anEntity [
	^ self new
		entity: anEntity;
		entityId: anEntity entityId;
		yourself
]

{ #category : 'applying' }
CESimAddOp >> applyInContext: aContext [
	(aContext partitionForSpawnOf: entity)
		addEntity: entity
]

{ #category : 'accessing' }
CESimAddOp >> entity [
	^ entity
]

{ #category : 'accessing' }
CESimAddOp >> entity: anObject [
	entity := anObject
]

{ #category : 'applying' }
CESimAddOp >> partitionInContext: aContext [
	^ entity spawnPartitionInContext: aContext
]
