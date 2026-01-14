Class {
	#name : 'CESimUpdate',
	#superclass : 'Object',
	#instVars : [
		'entityOps',
		'patches',
		'events'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CESimUpdate >> addEntityOp: anOp [
	entityOps add: anOp
]

{ #category : 'accessing' }
CESimUpdate >> addEvent: anEvent [
	events add: anEvent
]

{ #category : 'accessing' }
CESimUpdate >> addPatch: aPatch [
	patches add: aPatch
]

{ #category : 'accessing' }
CESimUpdate >> entityOps [
	^ entityOps
]

{ #category : 'accessing' }
CESimUpdate >> events [
	^ events
]

{ #category : 'initialization' }
CESimUpdate >> initialize [
	super initialize.
	entityOps := OrderedCollection new.
	patches := OrderedCollection new.
	events := OrderedCollection new
]

{ #category : 'testing' }
CESimUpdate >> isEmpty [
	^ entityOps isEmpty and: [ patches isEmpty and: [ events isEmpty ] ]
]

{ #category : 'accessing' }
CESimUpdate >> patches [
	^ patches
]

{ #category : 'printing' }
CESimUpdate >> printOn: aStream [
	aStream
		nextPutAll: self class name asString;
		nextPutAll: '(ops=';
		nextPutAll: entityOps size asString;
		nextPutAll: ', patches=';
		nextPutAll: patches size asString;
		nextPutAll: ', events=';
		nextPutAll: events size asString;
		nextPut: $)
]
