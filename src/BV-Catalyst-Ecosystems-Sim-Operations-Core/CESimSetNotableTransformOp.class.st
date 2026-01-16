Class {
	#name : 'CESimSetNotableTransformOp',
	#superclass : 'CESimEntitySpatialOp',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimSetNotableTransformOp class >> withRegionId: aCERegionId entityId: aCEEntityId transform: aTransformDict [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		transform: aTransformDict;
		yourself
]

{ #category : 'applying' }
CESimSetNotableTransformOp >> applyInContext: aCESimRunContext [
	(self notableInContext: aCESimRunContext) transform: transform
]

{ #category : 'accessing' }
CESimSetNotableTransformOp >> transform: aTransformDict [
	transform := aTransformDict
]
