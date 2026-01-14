Class {
	#name : 'CESimRunContext',
	#superclass : 'Object',
	#instVars : [
		'engine',
		'tickId',
		'environmentQuery',
		'subject',
		'updates',
		'stepCache'
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
CESimRunContext >> clearStepCache [
	stepCache removeAll
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

{ #category : 'step cache' }
CESimRunContext >> hasStepCacheKey: aKey [
    ^ stepCache includesKey: aKey
]

{ #category : 'initialization' }
CESimRunContext >> initialize [
	super initialize.
	updates := OrderedCollection new.
	stepCache := Dictionary new
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
CESimRunContext >> stepCache [
	^ stepCache
]

{ #category : 'step cache' }
CESimRunContext >> stepCacheAt: aKey ifAbsent: aBlock [
	^ stepCache at: aKey ifAbsent: aBlock
]

{ #category : 'step cache' }
CESimRunContext >> stepCacheAt: aKey put: aValue [
	stepCache at: aKey put: aValue
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
