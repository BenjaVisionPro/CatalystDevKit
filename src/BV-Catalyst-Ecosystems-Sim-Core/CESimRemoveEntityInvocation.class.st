Class {
	#name : 'CESimRemoveEntityInvocation',
	#superclass : 'CESimTargetedInvocation',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimRemoveEntityInvocation >> contributeIntoUpdate: aUpdate inContext: aContext [
	aUpdate addEntityOp: (CESimRemoveOp entityId: targetEntityId)
]
