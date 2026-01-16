Class {
	#name : 'CESimRemoveNotableFromRegionOp',
	#superclass : 'CESimEntityLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimRemoveNotableFromRegionOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) removeNotableId: entityId
]
