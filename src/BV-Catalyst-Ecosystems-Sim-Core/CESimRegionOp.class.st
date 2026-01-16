Class {
	#name : 'CESimRegionOp',
	#superclass : 'CESimEntityOp',
	#instVars : [
		'regionId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimRegionOp class >> withRegionId: aCERegionId [
	^ self new regionId: aCERegionId; yourself
]

{ #category : 'ordering' }
CESimRegionOp >> primarySortValue [
	"Sort by region id when no entity id is available."
	^ regionId asInteger
]

{ #category : 'accessing' }
CESimRegionOp >> regionId [
	^ regionId
]

{ #category : 'accessing' }
CESimRegionOp >> regionId: aCERegionId [
	regionId := aCERegionId
]

{ #category : 'resolving' }
CESimRegionOp >> regionInContext: aCESimRunContext [
	^ aCESimRunContext engine ensureRegion: regionId
]
