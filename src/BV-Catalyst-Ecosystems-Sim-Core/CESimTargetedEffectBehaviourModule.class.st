Class {
	#name : 'CESimTargetedEffectBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'private - targeting' }
CESimTargetedEffectBehaviourModule >> bubbleInContext: aCESimRunContext [
	^ aCESimRunContext subject
]

{ #category : 'as yet unclassified' }
CESimTargetedEffectBehaviourModule >> gateTargetEntityId: anEntityId forCommand: aCommand module: aModuleSymbol intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	^ aCESimRunContext
		gateTargetEntityId: anEntityId
		forCommand: aCommand
		module: aModuleSymbol
		intoUpdate: aCESimUpdate
]

{ #category : 'private - targeting' }
CESimTargetedEffectBehaviourModule >> homeRegionIdInContext: aCESimRunContext [
	^ (self bubbleInContext: aCESimRunContext) homeRegionId
]

{ #category : 'private - targeting' }
CESimTargetedEffectBehaviourModule >> regionInContext: aCESimRunContext [
	| engine regionId |
	engine := aCESimRunContext engine.
	regionId := self homeRegionIdInContext: aCESimRunContext.
	^ engine ensureRegion: regionId
]

{ #category : 'private - targeting' }
CESimTargetedEffectBehaviourModule >> withPerceivedVisibleNotablesInContext: aCESimRunContext do: aBlock [
	| region snapshots |
	region := self regionInContext: aCESimRunContext.
	snapshots := self perceivedVisibleSnapshotsInContext: aCESimRunContext.

	snapshots do: [ :snap |
		| entityId notable |
		entityId := snap at: #entityId.
		notable := region notableAt: entityId.
		aBlock value: notable value: entityId value: snap
	]
]
