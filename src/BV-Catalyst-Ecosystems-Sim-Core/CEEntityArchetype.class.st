Class {
	#name : 'CEEntityArchetype',
	#superclass : 'Object',
	#instVars : [
		'archetypeId',
		'tags',
		'displayName'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CEEntityArchetype >> archetypeId [
	^ archetypeId
]

{ #category : 'accessing' }
CEEntityArchetype >> archetypeId: anObject [
	archetypeId := anObject
]

{ #category : 'accessing' }
CEEntityArchetype >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CEEntityArchetype >> displayName: anObject [
	displayName := anObject
]

{ #category : 'initialization' }
CEEntityArchetype >> initialize [
	super initialize.
	tags := OrderedCollection new
]

{ #category : 'accessing' }
CEEntityArchetype >> tags [
	^ tags
]

{ #category : 'accessing' }
CEEntityArchetype >> tags: anObject [
	tags := anObject
]
