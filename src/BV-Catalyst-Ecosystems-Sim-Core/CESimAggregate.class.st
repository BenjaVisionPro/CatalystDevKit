Class {
	#name : 'CESimAggregate',
	#superclass : 'Object',
	#instVars : [
		'aggregateId',
		'eventLog'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimAggregate class >> withId: aCEStableId [
    ^ self new withId: aCEStableId
]

{ #category : 'accessing' }
CESimAggregate >> aggregateId [
	^ aggregateId
]

{ #category : 'accessing' }
CESimAggregate >> appendEvent: anEvent [
	eventLog add: anEvent
]

{ #category : 'accessing' }
CESimAggregate >> eventLog [
	^ eventLog copy
]

{ #category : 'initialization' }
CESimAggregate >> initialize [
	eventLog := OrderedCollection new
]

{ #category : 'printing' }
CESimAggregate >> printOn: aStream [
	aStream
		nextPutAll: self typeLabel;
		nextPut: $(;
		print: aggregateId;
		nextPutAll: ', events=';
		nextPutAll: eventLog size asString;
		nextPut: $)
]

{ #category : 'accessing' }
CESimAggregate >> typeLabel [
    "Subclasses override."
    ^ self class name asString
]

{ #category : 'initialization' }
CESimAggregate >> withId: aCEStableId [
	aggregateId := aCEStableId
]
