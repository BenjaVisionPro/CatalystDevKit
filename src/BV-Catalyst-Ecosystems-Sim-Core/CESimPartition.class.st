Class {
	#name : 'CESimPartition',
	#superclass : 'CESimAggregate',
	#instVars : [
		'entitiesById',
		'invocationInbox'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'notables' }
CESimPartition >> addEntity: anEntity [
	entitiesById at: anEntity entityId put: anEntity
]

{ #category : 'inbox' }
CESimPartition >> enqueueInvocationEnvelope: anEnvelope [
	"I enqueue an invocation envelope so I can execute it on my next tick. I rely on my inbox to dedupe duplicates."

	invocationInbox enqueue: anEnvelope
]

{ #category : 'notables' }
CESimPartition >> entities [
	"Deterministic ordering: by entityId backing value."

	^ (entitiesById values
		asSortedCollection: [ :a :b | a entityId value < b entityId value ])
		asOrderedCollection
]

{ #category : 'notables' }
CESimPartition >> entityAt: anEntityId [
	^ self entityAt: anEntityId ifAbsent: [ nil ]
]

{ #category : 'notables' }
CESimPartition >> entityAt: anEntityId ifAbsent: aBlock [
    ^ entitiesById at: anEntityId ifAbsent: aBlock
]

{ #category : 'notables' }
CESimPartition >> includesEntityId: anEntityId [
	^ entitiesById includesKey: anEntityId
]

{ #category : 'initialization' }
CESimPartition >> initialize [
	super initialize.
	entitiesById := Dictionary new.
	invocationInbox := CESimDedupingInbox
			orderedBy: [ :anEnvelope | anEnvelope envelopeId ]
			dedupeBy: [ :anEnvelope | anEnvelope envelopeId ]
]

{ #category : 'inbox' }
CESimPartition >> invocationInbox [
	^ invocationInbox
]

{ #category : 'as yet unclassified' }
CESimPartition >> partitionId [
	^ aggregateId
]

{ #category : 'notables' }
CESimPartition >> removeEntityId: anEntityId [
	entitiesById removeKey: anEntityId ifAbsent: [  ]
]
