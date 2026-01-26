Class {
	#name : 'CESimAggregate',
	#superclass : 'Object',
	#instVars : [
		'aggregateId',
		'eventLog',
		'commands',
		'invocations'
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

{ #category : 'commnands' }
CESimAggregate >> drainCommands [
	| drained |
	drained := commands.
	commands := OrderedCollection new.
	^ drained
]

{ #category : 'invocations' }
CESimAggregate >> drainInvocations [
	| drained |
	drained := invocations.
	invocations := OrderedCollection new.
	^ drained
]

{ #category : 'commnands' }
CESimAggregate >> enqueueCommand: aCommand [
	commands add: aCommand
]

{ #category : 'invocations' }
CESimAggregate >> enqueueInvocation: anInvocation [
	invocations add: anInvocation
]

{ #category : 'accessing' }
CESimAggregate >> eventLog [
	^ eventLog copy
]

{ #category : 'initialization' }
CESimAggregate >> initialize [
	eventLog := OrderedCollection new.
	commands := OrderedCollection new.
	invocations := OrderedCollection new.
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
