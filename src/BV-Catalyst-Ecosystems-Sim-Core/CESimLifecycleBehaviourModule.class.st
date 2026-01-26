Class {
	#name : 'CESimLifecycleBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimLifecycleBehaviourModule >> applyCreateNotableCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId notable |
	regionId := aCESimRunContext subject partitionId.

	"IDs are minted here (context factory), not in the command event path."
	notable := aCESimRunContext
		newEntityWithDefinitionKey: aCommand spawnSpecId
		transform: aCommand transform
		state: aCommand state.

	aCESimUpdate addEntityOp: (CESimAddOp
		withRegionId: regionId
		entity: notable)
]

{ #category : 'applying' }
CESimLifecycleBehaviourModule >> applyRemoveNotableCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := aCESimRunContext subject partitionId.

	aCESimUpdate addEntityOp: (CESimRemoveOp
		withRegionId: regionId
		entityId: aCommand entityId)
]

{ #category : 'contributing' }
CESimLifecycleBehaviourModule >> contributeIntoUpdate: aUpdate inContext: aContext [
	| commands |
	commands := aContext runCache drainedCommands.
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd contributeInvocationsIntoUpdate: aUpdate inContext: aContext ] ].

	aContext runCache invocations
		do: [ :inv | 
			CESimCurrentOrigin
				value: inv
				during: [ inv contributeIntoUpdate: aUpdate inContext: aContext ] ]
]
