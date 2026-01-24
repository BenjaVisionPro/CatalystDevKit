Class {
	#name : 'CESimAddEntityCommand',
	#superclass : 'CESimExternalCommand',
	#instVars : [
		'transform',
				'spawnSpecId',
		'entityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimAddEntityCommand class >> withSpawnSpecId: aSpecId transform: aTransform [
	^ self new
		spawnSpecId: aSpecId;
		transform: aTransform;		yourself
]

{ #category : 'contributing' }
CESimAddEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext runCache
		addInvocation: (CESimAddEntityInvocation new
				spawnSpecId: spawnSpecId;
				transform: transform;
				entityId: entityId; "nil if not provided"
				yourself)
]

{ #category : 'contributing' }
{ #category : 'accessing' }
CESimAddEntityCommand >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimAddEntityCommand >> entityId: anObject [
	entityId := anObject
]

{ #category : 'producing' }
CESimAddEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #addEntityRequested;
		at: #spawnSpecId put: spawnSpecId;
		at: #transform put: transform;		at: #tickId put: aCESimRunContext tickId;
		yourself)
]

{ #category : 'accessing' }
CESimAddEntityCommand >> spawnSpecId [
	^ spawnSpecId
]

{ #category : 'accessing' }
CESimAddEntityCommand >> spawnSpecId: aKey [
	spawnSpecId := aKey
]

{ #category : 'accessing' }
{ #category : 'accessing' }
{ #category : 'accessing' }
CESimAddEntityCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform: aTransform [
	transform := aTransform
]
