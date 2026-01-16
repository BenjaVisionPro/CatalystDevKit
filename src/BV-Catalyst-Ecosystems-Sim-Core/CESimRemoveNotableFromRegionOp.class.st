Class {
	#name : 'CESimRemoveNotableFromRegionOp',
	#superclass : 'CESimEntityLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimRemoveNotableFromRegionOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) removeNotableId: entityId
]