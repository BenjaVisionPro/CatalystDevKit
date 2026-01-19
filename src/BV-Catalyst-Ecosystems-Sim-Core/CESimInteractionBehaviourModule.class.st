Class {
	#name : 'CESimInteractionBehaviourModule',
	#superclass : 'CESimPatchEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimInteractionBehaviourModule >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| commands |
	commands := aCESimRunContext runCache drainedCommands.

	commands do: [ :cmd |
		cmd
			contributeToInteractionBehaviourModule: self
			intoUpdate: aCESimUpdate
			inContext: aCESimRunContext
	]
]