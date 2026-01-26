Class {
	#name : 'CESimSetTransformOp',
	#superclass : 'CESimSpatialOp',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimSetTransformOp class >> entityId: anEntityId transform: aTransform [
	^ self new
		entityId: anEntityId;
		transform: aTransform;
		yourself
]

{ #category : 'applying' }
CESimSetTransformOp >> applyInContext: aContext [
	| partition entity |
	partition := aContext engine
			partitionContainingEntityId: entityId
			ifNone: [ ^ self ].

	entity := partition entityAt: entityId ifAbsent: [ ^ self ].
	entity applyTransform: transform
]

{ #category : 'accessing' }
CESimSetTransformOp >> transform: aTransformDict [
	transform := aTransformDict
]
