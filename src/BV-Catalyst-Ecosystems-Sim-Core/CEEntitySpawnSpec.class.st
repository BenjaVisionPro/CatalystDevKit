Class {
	#name : 'CEEntitySpawnSpec',
	#superclass : 'Object',
	#instVars : [
		'spawnSpecId',
		'archetypeId',
		'entityClass',
		'appellation',
		'initialState',
		'moduleSpecs'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CEEntitySpawnSpec >> appellation [
	^ appellation
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> appellation: anObject [
	appellation := anObject
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> archetypeId [
	^ archetypeId
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> archetypeId: anObject [
	archetypeId := anObject
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> entityClass [
	^ entityClass
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> entityClass: anObject [
	entityClass := anObject
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> initialState [
	^ initialState
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> initialState: anObject [
	initialState := anObject
]

{ #category : 'initialization' }
CEEntitySpawnSpec >> initialize [
	super initialize.
	moduleSpecs := OrderedCollection new
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> moduleSpecs [
	^ moduleSpecs
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> moduleSpecs: anObject [
	moduleSpecs := anObject
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> spawnSpecId [
	^ spawnSpecId
]

{ #category : 'accessing' }
CEEntitySpawnSpec >> spawnSpecId: anObject [
	spawnSpecId := anObject
]
