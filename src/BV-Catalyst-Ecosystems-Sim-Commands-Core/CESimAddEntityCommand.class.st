Class {
	#name : 'CESimAddEntityCommand',
	#superclass : 'CESimCommand',
	#instVars : [
		'transform',
		'spawnSpecId',
		'entityId',
		'stateOverlay'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimAddEntityCommand class >> withSpawnSpecId: aSpecId transform: aTransform stateOverlay: aStateOverlay [
	^ self new
		spawnSpecId: aSpecId;
		transform: aTransform;
		stateOverlay: aStateOverlay;
		yourself
]

{ #category : 'contributing' }
CESimAddEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext subject
		enqueueInvocation: (CESimAddEntityInvocation new
				spawnSpecId: spawnSpecId;
				transform: transform;
				targetEntityId: entityId;
				stateOverlay: stateOverlay;
				yourself)
]

{ #category : 'accessing' }
CESimAddEntityCommand >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimAddEntityCommand >> entityId: anObject [
	entityId := anObject
]

{ #category : 'producing' }
CESimAddEntityCommand >> produceEventsIntoUpdate: aUpdate inContext: aContext [
	aUpdate
		addEvent: (Dictionary new
				at: #type put: #addEntityRequested;
				at: #spawnSpecId put: spawnSpecId;
				at: #transform put: transform;
				at: #stateOverlay put: stateOverlay;
				at: #entityId put: entityId;
				at: #tickId put: aContext tickId;
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
CESimAddEntityCommand >> stateOverlay [
	^ stateOverlay
]

{ #category : 'accessing' }
CESimAddEntityCommand >> stateOverlay: aState [
	stateOverlay := aState
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform: aTransform [
	transform := aTransform
]
