Class {
	#name : 'CESimEntityOp',
	#superclass : 'CESimOp',
	#instVars : [
		'entityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimEntityOp class >> entityId: anEntityId [
	^ self new
		entityId: anEntityId;
		yourself
]

{ #category : 'applying' }
CESimEntityOp >> applyInContext: aCESimRunContext [
	self subclassResponsibility
]

{ #category : 'ordering' }
CESimEntityOp >> before: anotherOp [
	| aOrder bOrder |
	aOrder := self opOrder.
	bOrder := anotherOp opOrder.
	aOrder = bOrder ifFalse: [ ^ aOrder < bOrder ].

	^ self entityId < anotherOp entityId
]

{ #category : 'accessing' }
CESimEntityOp >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimEntityOp >> entityId: anObject [
	entityId := anObject
]

{ #category : 'ordering' }
CESimEntityOp >> opOrder [
	"Lower applies first. Subclasses override."
	^ 0
]

{ #category : 'ordering' }
CESimEntityOp >> primarySortValue [
	"Secondary deterministic sort value."
	^ 0
]
