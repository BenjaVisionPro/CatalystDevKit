Class {
	#name : 'CEStableId',
	#superclass : 'Object',
	#instVars : [
		'value'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CEStableId class >> fromInteger: anInteger [
    "Used for deserialization, tests, and tooling. Not for allocation."
    ^ self new initializeFromInteger: anInteger
]

{ #category : 'comparing' }
CEStableId >> < other [
    (other class == self class) ifFalse: [
        self error: 'Cannot compare different ID types: ', self class name, ' vs ', other class name ].
    ^ value < other asInteger
]

{ #category : 'comparing' }
CEStableId >> = other [
    self == other ifTrue: [ ^ true ].
    (other class == self class) ifFalse: [ ^ false ].
    ^ value = other asInteger
]

{ #category : 'conversion' }
CEStableId >> asInteger [
    ^ value
]

{ #category : 'conversion' }
CEStableId >> asString [
    ^ value asString
]

{ #category : 'comparing' }
CEStableId >> hash [
    "Include class to avoid accidental cross-type equality collisions."
    ^ (self class hash bitXor: value hash)
]

{ #category : 'initialization' }
CEStableId >> initializeFromInteger: anInteger [
    value := anInteger.
    ^ self
]

{ #category : 'printing' }
CEStableId >> printOn: aStream [
    aStream
        nextPutAll: self typeLabel;
        nextPut: $(;
        nextPutAll: value asString;
        nextPut: $)
]

{ #category : 'printing' }
CEStableId >> typeLabel [
    "Subclasses override."
    ^ self class name asString
]
