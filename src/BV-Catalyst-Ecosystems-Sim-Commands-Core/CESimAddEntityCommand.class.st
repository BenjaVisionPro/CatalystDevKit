Class {
	#name : 'CESimAddEntityCommand',
	#superclass : 'CESimExternalCommand',
	#instVars : [
		'transform',
		'state',
		'spawnSpecId',
		'entityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimAddEntityCommand class >> withSpawnSpecId: aSpecId transform: aTransform state: aState [
	^ self new
		spawnSpecId: aSpecId;
		transform: aTransform;
		state: aState;
		yourself
]

{ #category : 'contributing' }
CESimAddEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext runCache
		addInvocation: (CESimAddEntityInvocation new
				spawnSpecId: spawnSpecId;
				transform: transform;
				yourself)
]

{ #category : 'contributing' }
CESimAddEntityCommand >> contributeLifecycleIntoUpdate: aUpdate inContext: aContext [
	aContext runCache addInvocation: (CESimAddEntityInvocation new
		spawnSpecId: spawnSpecId;
		transform: transform;
		entityId: entityId; "nil if not provided"
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
CESimAddEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #createNotableRequested;
		at: #spawnSpecId put: spawnSpecId;
		at: #transform put: transform;
		at: #state put: state;
		at: #tickId put: aCESimRunContext tickId;
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
CESimAddEntityCommand >> state [
	^ state
]

{ #category : 'accessing' }
CESimAddEntityCommand >> state: aState [
	state := aState
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform: aTransform [
	transform := aTransform
]
