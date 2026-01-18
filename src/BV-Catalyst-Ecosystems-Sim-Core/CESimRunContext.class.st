Class {
	#name : 'CESimRunContext',
	#superclass : 'Object',
	#instVars : [
		'engine',
		'tickId',
		'environmentQuery',
		'subject',
		'updates',
		'runCache'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimRunContext class >> for: aSubject engine: anEngine tickId: aTickId environmentQuery: anEnvironmentQuery [
	^ self new
		engine: anEngine;
		tickId: aTickId;
		environmentQuery: anEnvironmentQuery;
		subject: aSubject;
		yourself
]

{ #category : 'updates' }
CESimRunContext >> addUpdate: aCESimUpdate [
	updates add: aCESimUpdate
]

{ #category : 'step cache' }
CESimRunContext >> clearRunCache [
	runCache removeAll
]

{ #category : 'updates' }
CESimRunContext >> clearUpdates [
	updates removeAll
]

{ #category : 'accessing' }
CESimRunContext >> engine [
	^ engine
]

{ #category : 'accessing' }
CESimRunContext >> engine: anObject [
	engine := anObject
]

{ #category : 'accessing' }
CESimRunContext >> environmentQuery [
	^ environmentQuery
]

{ #category : 'accessing' }
CESimRunContext >> environmentQuery: anObject [
	environmentQuery := anObject
]

{ #category : 'initialization' }
CESimRunContext >> initialize [
	super initialize.
	updates := OrderedCollection new.
	runCache := CESimRunCache new
]

{ #category : 'entities' }
CESimRunContext >> newNotableWithDefinitionKey: aKey transform: aTransform state: aState [
	| entityId |
	entityId := engine idIssuer nextEntityId.
	^ CENotable
		id: entityId
		definitionKey: aKey
		transform: aTransform
		state: aState
]

{ #category : 'printing' }
CESimRunContext >> printOn: aStream [
    aStream
        nextPutAll: self class name asString;
        nextPutAll: '(tick=';
        nextPutAll: tickId asString;
        nextPutAll: ', subject=';
        print: subject;
        nextPut: $)
]

{ #category : 'step cache' }
CESimRunContext >> runCache [
	^ runCache
]

{ #category : 'step cache' }
CESimRunContext >> runCacheAt: aKey ifAbsent: aBlock [
	^ runCache at: aKey ifAbsent: aBlock
]

{ #category : 'step cache' }
CESimRunContext >> runCacheAt: aKey put: aValue [
	runCache at: aKey put: aValue
]

{ #category : 'accessing' }
CESimRunContext >> subject [
	^ subject
]

{ #category : 'accessing' }
CESimRunContext >> subject: anObject [
	subject := anObject
]

{ #category : 'accessing' }
CESimRunContext >> tickId [
	^ tickId
]

{ #category : 'accessing' }
CESimRunContext >> tickId: anObject [
	tickId := anObject
]

{ #category : 'updates' }
CESimRunContext >> updates [
	^ updates copy
]
