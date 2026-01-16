Class {
	#name : 'CESequenceIdIssuer',
	#superclass : 'Object',
	#instVars : [
		'nextRegionInt',
		'nextBubbleInt',
		'nextEntityInt'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'initialization' }
CESequenceIdIssuer >> initialize [
	super initialize.
	nextRegionInt := 1.
	nextBubbleInt := 1.
	nextEntityInt := 1
]

{ #category : 'issuing' }
CESequenceIdIssuer >> nextBubbleId [
    | id |
    id := CEBubbleId fromInteger: nextBubbleInt.
    nextBubbleInt := nextBubbleInt + 1.
    ^ id
]

{ #category : 'issuing' }
CESequenceIdIssuer >> nextEntityId [
    | id |
    id := CEEntityId fromInteger: nextEntityInt.
    nextEntityInt := nextEntityInt + 1.
    ^ id
]

{ #category : 'issuing' }
CESequenceIdIssuer >> nextRegionId [
	| id |
	id := CERegionId fromInteger: nextRegionInt.
	nextRegionInt := nextRegionInt + 1.
	^ id
]
