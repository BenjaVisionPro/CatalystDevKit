Class {
	#name : 'CESimRemoveOp',
	#superclass : 'CESimLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimRemoveOp >> applyInContext: aContext [
	| partition |
	partition := aContext engine
			partitionContainingEntityId: self entityId
			ifNone: [ ^ self ].

	partition removeEntityId: self entityId
]
