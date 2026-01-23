Class {
	#name : 'CESimAddEntityToRegionOp',
	#superclass : 'CESimEntityLifecycleOp',
	#instVars : [
		'entity'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimAddEntityToRegionOp class >> withRegionId: aCERegionId entity: anEntity [
	^ self new
		regionId: aCERegionId;
		entityId: anEntity entityId;
		entity: anEntity;
		yourself
]

{ #category : 'applying' }
CESimAddEntityToRegionOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) addEntity: entity
]

{ #category : 'accessing' }
CESimAddEntityToRegionOp >> entity: anEntity [
	entity := anEntity
]
