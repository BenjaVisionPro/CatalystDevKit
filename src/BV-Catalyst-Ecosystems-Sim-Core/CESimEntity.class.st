Class {
	#name : 'CESimEntity',
	#superclass : 'Object',
	#instVars : [
		'entityId',
		'definitionKey',
		'moduleStates',
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimEntity class >> id: aCEEntityId definitionKey: aDefinitionKey [
	^ self new
		entityId: aCEEntityId;
		definitionKey: aDefinitionKey;
		initializeModuleStates;
		yourself
]

{ #category : 'as yet unclassified' }
CESimEntity >> asSnapshot [
	| snap |
	snap := Dictionary new
			at: #entityId put: entityId;
			at: #definitionKey put: definitionKey;
			at: #state put: state;
			yourself.
	^ snap
]

{ #category : 'accessing' }
CESimEntity >> definitionKey [
	^ definitionKey
]

{ #category : 'accessing' }
CESimEntity >> definitionKey: anObject [
	definitionKey := anObject
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
CESimEntity >> state [
	^ state
]

{ #category : 'accessing' }
CESimEntity >> state: anObject [
	state := anObject
]
