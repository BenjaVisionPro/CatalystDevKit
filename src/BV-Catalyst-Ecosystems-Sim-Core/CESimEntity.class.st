Class {
	#name : 'CESimEntity',
	#superclass : 'Object',
	#instVars : [
		'entityId',
		'moduleStates',
		'state',
		'spawnSpecId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'spawning' }
CESimEntity class >> spawnFromSpec: aSpawnSpec entityId: anEntityId state: aState [
	| entity |
	entity := aSpawnSpec entityClass new.

	entity configureFromSpawnSpec: aSpawnSpec.
	entity entityId: anEntityId.
	entity state: aState.
	^ entity
]

{ #category : 'spawning' }
CESimEntity class >> spawnFromSpec: aSpec entityId: anEntityId transform: aTransform state: aState [
	| entity |
	entity := self spawnFromSpec: aSpec entityId: anEntityId state: aState.
	^ entity
]

{ #category : 'as yet unclassified' }
CESimEntity >> asSnapshot [
	| snap |
	snap := Dictionary new
			at: #entityId put: entityId;
			at: #spawnSpecId put: spawnSpecId;
			at: #state put: state;
			yourself.
	^ snap
]

{ #category : 'accessing' }
CESimEntity >> configureFromSpawnSpec: aSpawnSpec [
	"Configure intrinsic, type-level properties derived from the spawn spec."

	self spawnSpecId: aSpawnSpec spawnSpecId
]

{ #category : 'accessing' }
CESimEntity >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimEntity >> entityId: anObject [
	entityId := anObject
]

{ #category : 'initialization' }
CESimEntity >> initialize [
    super initialize.
    self initializeModuleStates
]

{ #category : 'initialization' }
CESimEntity >> initializeModuleStates [
    moduleStates := Dictionary new
]

{ #category : 'accessing' }
CESimEntity >> moduleStateAt: aKey ifAbsentPut: aBlock [
    ^ moduleStates at: aKey ifAbsentPut: aBlock
]

{ #category : 'accessing' }
CESimEntity >> moduleStates [
	^ moduleStates
]

{ #category : 'accessing' }
CESimEntity >> spawnSpecId [
	^ spawnSpecId
]

{ #category : 'accessing' }
CESimEntity >> spawnSpecId: anObject [
	spawnSpecId := anObject
]

{ #category : 'accessing' }
CESimEntity >> state [
	^ state
]

{ #category : 'accessing' }
CESimEntity >> state: anObject [
	state := anObject
]
