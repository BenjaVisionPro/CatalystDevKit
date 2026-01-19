Class {
	#name : 'CESimPatchEffectBehaviourModule',
	#superclass : 'CESimTargetedEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'private - patching' }
CESimPatchEffectBehaviourModule >> addNotablePatch: aPatch
	entityId: aCEEntityId
	inContext: aCESimRunContext
	intoUpdate: aCESimUpdate [
	| regionId |
	regionId := self homeRegionIdInContext: aCESimRunContext.

	aCESimUpdate addEntityOp: (CESimPatchNotableStateOp
		withRegionId: regionId
		entityId: aCEEntityId
		patch: aPatch)
]