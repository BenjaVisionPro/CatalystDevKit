Class {
	#name : 'CESimDedupingInbox',
	#superclass : 'CESimInbox',
	#instVars : [
		'dedupeKeyBlock',
		'seenKeys'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimDedupingInbox class >> orderedBy: aSortKeyBlock dedupeBy: aDedupeKeyBlock [
	^ self new
		sortKeyBlock: aSortKeyBlock;
		dedupeKeyBlock: aDedupeKeyBlock;
		yourself
]

{ #category : 'accessing' }
CESimDedupingInbox >> dedupeKeyBlock [
	^ dedupeKeyBlock
]

{ #category : 'accessing' }
CESimDedupingInbox >> dedupeKeyBlock: aDedupeKeyBlock [
	dedupeKeyBlock := aDedupeKeyBlock
]

{ #category : 'enqueueing' }
CESimDedupingInbox >> enqueue: anObject [
	| key |
	key := dedupeKeyBlock value: anObject.
	(seenKeys includes: key) ifTrue: [ ^ self ].
	seenKeys add: key.
	^ super enqueue: anObject
]

{ #category : 'initialization' }
CESimDedupingInbox >> initialize [
	super initialize.
	seenKeys := Set new.
	"Default: identity key. Usually callers configure via class-side constructor."
	dedupeKeyBlock := [ :each | each ]
]

{ #category : 'maintenance' }
CESimDedupingInbox >> resetDedupe [
	seenKeys := Set new
]
