Class {
	#name : 'CESimRemoveOp',
	#superclass : 'CESimLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimRemoveOp >> applyInContext: aContext [
	(aContext partitionForEntityId: entityId) removeEntityId: entityId
]
