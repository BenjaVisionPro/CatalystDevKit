Class {
	#name : 'CESimAddOp',
	#superclass : 'CESimLifecycleOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimAddOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) addEntity: entityId
]
