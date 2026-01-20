Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimTargetedEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimStimulusBehaviourModule >> applyStimulusCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := self homeRegionIdInContext: aCESimRunContext.
	
	"Target current perceived visibility (this tick's observation set)." 
	(aCESimRunContext runCache perceivedVisibleSnapshots) 
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
