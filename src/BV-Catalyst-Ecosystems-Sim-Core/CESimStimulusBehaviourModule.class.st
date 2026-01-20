Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimStimulusBehaviourModule >> applyStimulusCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := aCESimRunContext subject homeRegionId.

	"Non-targeted: affects whatever is perceived this tick."
	(self perceivedVisibleSnapshotsInContext: aCESimRunContext)
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
