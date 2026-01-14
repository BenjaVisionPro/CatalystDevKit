Class {
	#name : 'CESimLocalView',
	#superclass : 'Object',
	#instVars : [
		'bubbleId',
		'tickId',
		'events',
		'spawns',
		'updates',
		'despawns'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimLocalView class >> bubbleId: aCEBubbleId tickId: aTickId events: anEventCollection [
	^ self new
		bubbleId: aCEBubbleId;
		tickId: aTickId;
		events: anEventCollection;
		yourself
]

{ #category : 'accessing' }
CESimLocalView >> bubbleId [
	^ bubbleId
]

{ #category : 'accessing' }
CESimLocalView >> bubbleId: anObject [
	bubbleId := anObject
]

{ #category : 'accessing' }
CESimLocalView >> despawns [
	^ despawns
]

{ #category : 'accessing' }
CESimLocalView >> despawns: anObject [
	despawns := anObject
]

{ #category : 'accessing' }
CESimLocalView >> events [
	^ events
]

{ #category : 'accessing' }
CESimLocalView >> events: anObject [
	events := anObject asOrderedCollection
]

{ #category : 'initialization' }
CESimLocalView >> initialize [
	super initialize.
	events := OrderedCollection new.
	spawns := OrderedCollection new.
	updates := OrderedCollection new.
	despawns := OrderedCollection new
]

{ #category : 'printing' }
CESimLocalView >> printOn: aStream [
	aStream
		nextPutAll: self class name asString;
		nextPut: $(;
		print: bubbleId;
		nextPutAll: ', tick=';
		nextPutAll: tickId asString;
		nextPutAll: ', events=';
		nextPutAll: events size asString;
		nextPut: $)
]

{ #category : 'accessing' }
CESimLocalView >> spawns [
	^ spawns
]

{ #category : 'accessing' }
CESimLocalView >> spawns: anObject [
	spawns := anObject
]

{ #category : 'accessing' }
CESimLocalView >> tickId [
	^ tickId
]

{ #category : 'accessing' }
CESimLocalView >> tickId: anObject [
	tickId := anObject
]

{ #category : 'accessing' }
CESimLocalView >> updates [
	^ updates
]

{ #category : 'accessing' }
CESimLocalView >> updates: anObject [
	updates := anObject
]
