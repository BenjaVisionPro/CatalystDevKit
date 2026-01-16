Class {
	#name : 'CESimSetNotableTransformOp',
	#superclass : 'CESimEntitySpatialOp',
	#instVars : [ 'transform' ],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimSetNotableTransformOp class >> withRegionId: aCERegionId entityId: aCEEntityId transform: aTransformDict [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		transform: aTransformDict;
		yourself
]

{ #category : 'accessing' }
CESimSetNotableTransformOp >> transform: aTransformDict [
	transform := aTransformDict
]

{ #category : 'applying' }
CESimSetNotableTransformOp >> applyInContext: aCESimRunContext [
	(self notableInContext: aCESimRunContext) transform: transform
]