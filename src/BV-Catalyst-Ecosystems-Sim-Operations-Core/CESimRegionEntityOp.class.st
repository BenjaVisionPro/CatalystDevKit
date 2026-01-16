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
CESimRegionEntityOp >> notableInContext: aCESimRunContext [
	^ (self regionInContext: aCESimRunContext)
		notableAt: entityId
		ifAbsent: [ self error: 'Notable not found: ', entityId asString ]
]

{ #category : 'ordering' }
CESimRegionEntityOp >> primarySortValue [
	^ entityId asInteger
]
