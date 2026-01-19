Class {
	#name : 'CESimLifecycleBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimLifecycleBehaviourModule >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| commands |
	commands := aCESimRunContext runCache drainedCommands.

	commands do: [ :cmd |
		cmd
			contributeToLifecycleBehaviourModule: self
			intoUpdate: aCESimUpdate
			inContext: aCESimRunContext
	]
]

{ #category : 'applying' }
CESimLifecycleBehaviourModule >> applyCreateNotableCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId notable |
	regionId := aCESimRunContext subject homeRegionId.

	"IDs are minted here (context factory), not in the command event path."
	notable := aCESimRunContext
		newNotableWithDefinitionKey: aCommand definitionKey
		transform: aCommand transform
		state: aCommand state.

	aCESimUpdate addEntityOp: (CESimAddNotableToRegionOp
		withRegionId: regionId
		notable: notable)
]