Class {
	#name : 'CESimSetEntityTransformOp',
	#superclass : 'CESimEntitySpatialOp',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimSetEntityTransformOp class >> withRegionId: aCERegionId entityId: aCEEntityId transform: aTransformDict [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		transform: aTransformDict;
		yourself
]

{ #category : 'applying' }
CESimSetEntityTransformOp >> applyInContext: aCESimRunContext [
	(self entityInContext: aCESimRunContext) transform: transform
]

{ #category : 'accessing' }
CESimSetEntityTransformOp >> transform: aTransformDict [
	transform := aTransformDict
]
