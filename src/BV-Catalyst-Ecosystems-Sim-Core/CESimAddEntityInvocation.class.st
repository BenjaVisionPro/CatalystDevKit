Class {
	#name : 'CESimAddEntityInvocation',
	#superclass : 'CESimLifecycleInvocation',
	#instVars : [
		'entityId',
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
	actualEntityId := entityId
		ifNil: [ aContext engine idIssuer nextEntityId ]
		ifNotNil: [ entityId ].

	entity := aContext
		spawnEntityFromSpecId: spawnSpecId
		entityId: actualEntityId
		transform: transform
		stateOverlay: stateOverlay.

	aUpdate addEntityOp: (CESimAddOp entity: entity)
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> entityId: anObject [
	entityId := anObject
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
