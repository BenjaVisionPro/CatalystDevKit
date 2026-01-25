Class {
	#name : 'CESimSetTransformOp',
	#superclass : 'CESimSpatialOp',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimSetTransformOp >> applyInContext: aCESimRunContext [
	(self entityInContext: aCESimRunContext) transform: transform
]

{ #category : 'accessing' }
CESimSetTransformOp >> transform: aTransformDict [
	transform := aTransformDict
]
