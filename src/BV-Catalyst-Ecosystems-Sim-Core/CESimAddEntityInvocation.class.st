Class {
	#name : 'CESimAddEntityInvocation',
	#superclass : 'CESimTargetedInvocation',
	#instVars : [
		'transform',
		'spawnSpecId',
		'stateOverlay'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimAddEntityInvocation >> contributeIntoUpdate: aUpdate inContext: aContext [
	| actualEntityId entity |
	actualEntityId := targetEntityId
		ifNil: [ aContext engine idIssuer nextEntityId ]
		ifNotNil: [ targetEntityId ].

	entity := aContext
		spawnEntityFromSpecId: spawnSpecId
		entityId: actualEntityId
		transform: transform
		stateOverlay: stateOverlay.

	aUpdate addEntityOp: (CESimAddOp entity: entity)
]

{ #category : 'routing' }
CESimAddEntityInvocation >> routeOn: anInvocationRouter inContext: aContext [
	"I route using my spawn transform so I am delivered to the partition that owns my spawn location."

	^ anInvocationRouter partitionIdsForTransform: transform inContext: aContext
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> spawnSpecId [
	^ spawnSpecId
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> spawnSpecId: anObject [
	spawnSpecId := anObject
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> stateOverlay [
	^ stateOverlay
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> stateOverlay: anObject [
	stateOverlay := anObject
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> transform: anObject [
	transform := anObject
]
