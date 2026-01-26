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
CESimAddOp >> entity: anEntity [
	entity := anEntity.
	self entityId: anEntity entityId
]
