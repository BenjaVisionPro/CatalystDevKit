Class {
	#name : 'CESimRegionEntityOp',
	#superclass : 'CESimRegionOp',
	#instVars : [
		'entityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimRegionEntityOp class >> withRegionId: aCERegionId entityId: aCEEntityId [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		yourself
]

{ #category : 'accessing' }
CESimRegionEntityOp >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimRegionEntityOp >> entityId: aCEEntityId [
	entityId := aCEEntityId
]

{ #category : 'resolving' }
CESimRegionEntityOp >> entityInContext: aCESimRunContext [
	^ (self regionInContext: aCESimRunContext) entityAt: entityId
]

{ #category : 'ordering' }
CESimRegionEntityOp >> primarySortValue [
	^ entityId asInteger
]
