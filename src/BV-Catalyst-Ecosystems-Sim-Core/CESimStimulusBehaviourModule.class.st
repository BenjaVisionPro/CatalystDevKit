Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimPatchEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimStimulusBehaviourModule >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| commands |
	commands := aCESimRunContext runCache drainedCommands.

	commands do: [ :cmd |
		cmd
			contributeToStimulusBehaviourModule: self
			intoUpdate: aCESimUpdate
			inContext: aCESimRunContext
	]
]