Class {
	#name : 'CESimAddEntityInvocation',
	#superclass : 'CESimLifecycleInvocation',
	#instVars : [
		'entityId',
		'transform',
		'state',
		'spawnSpecId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimAddEntityInvocation class >> entityId: anEntityId definitionKey: aDefinitionKey transform: aTransform state: aState [
]

{ #category : 'as yet unclassified' }
CESimAddEntityInvocation >> contributeIntoUpdate: aUpdate inContext: aContext [
	| actualEntityId entity regionId |
	actualEntityId := entityId
			ifNil: [  aContext engine idIssuer nextEntityId ]
			ifNotNil: [ entityId ].

	entity := aContext
			spawnEntityFromSpecId: spawnSpecId
			entityId: actualEntityId
			transform: transform.

	regionId := aContext regionIdForTransform: transform.

	aUpdate
		addEntityOp: (CESimAddEntityToRegionOp withRegionId: regionId entity: entity)
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
CESimAddEntityInvocation >> state [
	^ state
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> state: anObject [
	state := anObject
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityInvocation >> transform: anObject [
	transform := anObject
]
