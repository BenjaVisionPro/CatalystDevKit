Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimPatchEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimStimulusBehaviourModule >> applyStimulusCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := self homeRegionIdInContext: aCESimRunContext.
	
	"v0 targeting: apply to all visible snapshots (deterministic order already)."
	(self visibleSnapshotsInContext: aCESimRunContext)
		do: [ :snap | 
			| entityId |
			entityId := snap at: #entityId.

			aCESimUpdate
				addEntityOp: (CESimApplyStimulusToNotableOp
						withRegionId: regionId
						entityId: entityId
						stimulusType: aCommand stimulusType
						transform: aCommand transform
						intensity: aCommand intensity
						tickId: aCESimRunContext tickId) ]
]

{ #category : 'producing' }
CESimStimulusBehaviourModule >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| commands |
	commands := aCESimRunContext runCache drainedCommands.

	commands
		do: [ :cmd | 
			cmd
				contributeToStimulusBehaviourModule: self
				intoUpdate: aCESimUpdate
				inContext: aCESimRunContext ]
]
