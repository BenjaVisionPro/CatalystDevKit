Class {
	#name : 'CESimTransformEntityInvocation',
	#superclass : 'CESimTargetedInvocation',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimTransformEntityInvocation class >> targetEntityId: anEntityId transform: aTransform [
	^ (self targetEntityId: anEntityId)
		transform: aTransform;
		yourself
]

{ #category : 'as yet unclassified' }
CESimTransformEntityInvocation >> contributeIntoUpdate: anUpdate inContext: aContext [
	"Targeting / policy checks will live here"

	anUpdate
		addEntityOp: (CESimSetTransformOp entityId: targetEntityId transform: transform)
]

{ #category : 'accessing' }
CESimTransformEntityInvocation >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimTransformEntityInvocation >> transform: anObject [
	transform := anObject
]
