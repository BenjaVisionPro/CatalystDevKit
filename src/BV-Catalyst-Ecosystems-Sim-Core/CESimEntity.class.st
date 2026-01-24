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

{ #category : 'instance creation' }
CESimEntity class >> id: aCEEntityId definitionKey: aDefinitionKey [
	^ self new
		entityId: aCEEntityId;
		spawnSpecId: aDefinitionKey;
		initializeModuleStates;
		yourself
]

{ #category : 'instance creation' }
CESimEntity class >> id: aCEEntityId spawnSpecId: aSpawnSpecId [
	^ self new
		entityId: aCEEntityId;
		spawnSpecId: aSpawnSpecId;
		initializeModuleStates;
		yourself
]

{ #category : 'spawning' }
CESimEntity class >> spawnFromSpec: aSpec entityId: anId transform: aTransform [
	| entity |
	entity := aSpec entityClass new.
	^ entity
		configureFromSpawnSpec: aSpec
		entityId: anId
		transform: aTransform
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

{ #category : 'spawning' }
CESimEntity >> configureFromSpawnSpec: aSpec entityId: anId transform: aTransform [
	spawnSpecId := aSpec spawnSpecId.
	entityId := anId.
	state := aSpec initialState copy
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
    moduleStates := Dictionary new.
]

{ #category : 'initialization' }
CESimEntity >> initializeModuleStates [
    moduleStates ifNil: [ moduleStates := Dictionary new ].
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
