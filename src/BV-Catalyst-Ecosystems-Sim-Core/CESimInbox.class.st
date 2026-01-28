Class {
	#name : 'CESimInbox',
	#superclass : 'Object',
	#instVars : [
		'items',
		'sortKeyBlock'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInbox class >> orderedBy: aSortKeyBlock [
	^ self new
		sortKeyBlock: aSortKeyBlock;
		yourself
]

{ #category : 'draining' }
CESimInbox >> drain [
	"Return queued items in deterministic order and empty the inbox." 
	| drained |
	drained := (items asSortedCollection: [ :a :b |
			| ka kb |
			ka := sortKeyBlock value: a.
			kb := sortKeyBlock value: b.
			ka = kb
				ifTrue: [ a printString < b printString ]
				ifFalse: [ ka < kb ] ]) asArray.
	items removeAll.
	^ drained
]

{ #category : 'enqueueing' }
CESimInbox >> enqueue: anObject [
	items add: anObject
]

{ #category : 'initialization' }
CESimInbox >> initialize [
	super initialize.
	items := OrderedCollection new.
	"Default: stable, identity key. Usually callers configure via #orderedBy:."
	sortKeyBlock := [ :each | each ]
]

{ #category : 'testing' }
CESimInbox >> isEmpty [
	^ items isEmpty
]

{ #category : 'accessing' }
CESimInbox >> size [
	^ items size
]

{ #category : 'accessing' }
CESimInbox >> sortKeyBlock [
	^ sortKeyBlock
]

{ #category : 'accessing' }
CESimInbox >> sortKeyBlock: aSortKeyBlock [
	sortKeyBlock := aSortKeyBlock
]
