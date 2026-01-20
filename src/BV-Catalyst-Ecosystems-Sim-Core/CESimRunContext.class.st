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

{ #category : 'run cache' }
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

{ #category : 'factory - entities' }
CESimRunContext >> newNotableWithDefinitionKey: aKey transform: aTransform state: aState [
	"Canonical creation path for Notables.
	 Callers never mint ids; context/engine owns determinism + id issuance."

	^ CENotable new
		definitionKey: aKey;
		transform: aTransform;
		state: aState;
		entityId: self engine idIssuer nextEntityId;
		yourself	"or whatever your issuer selector is"
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

{ #category : 'run cache' }
CESimRunContext >> runCache [
	^ runCache
]

{ #category : 'run cache' }
CESimRunContext >> runCacheAt: aKey ifAbsent: aBlock [
	^ runCache at: aKey ifAbsent: aBlock
]

{ #category : 'run cache' }
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
