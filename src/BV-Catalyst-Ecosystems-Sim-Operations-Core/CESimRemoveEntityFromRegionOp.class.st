Class {
	#name : 'CESimRemoveEntityFromRegionOp',
	#superclass : 'CESimEntityLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimRemoveEntityFromRegionOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) removeEntityId: entityId
]
