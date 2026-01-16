Class {
	#name : 'CESimEntityOp',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimEntityOp >> applyInContext: aCESimRunContext [
	self subclassResponsibility
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

{ #category : 'ordering' }
CESimEntityOp >> before: anotherOp [
	| aOrder bOrder aPrim bPrim |
	aOrder := self opOrder.
	bOrder := anotherOp opOrder.
	aOrder = bOrder ifFalse: [ ^ aOrder < bOrder ].

	aPrim := self primarySortValue.
	bPrim := anotherOp primarySortValue.
	aPrim = bPrim ifFalse: [ ^ aPrim < bPrim ].

	"Final tie-breaker: stable by class name"
	^ self class name asString < anotherOp class name asString
]