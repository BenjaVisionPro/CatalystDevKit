Class {
	#name : 'CESimLifecycleBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimLifecycleBehaviourModule >> applyCreateNotableCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId notable |
	regionId := aCESimRunContext subject homeRegionId.

	"IDs are minted here (context factory), not in the command event path."
	notable := aCESimRunContext
		newEntityWithDefinitionKey: aCommand definitionKey
		transform: aCommand transform
		state: aCommand state.

	aCESimUpdate addEntityOp: (CESimAddEntityToRegionOp
		withRegionId: regionId
		entity: notable)
]

{ #category : 'applying' }
CESimLifecycleBehaviourModule >> applyRemoveNotableCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := aCESimRunContext subject homeRegionId.

	aCESimUpdate addEntityOp: (CESimRemoveEntityFromRegionOp
		withRegionId: regionId
		entityId: aCommand entityId)
]

{ #category : 'contributing' }
CESimLifecycleBehaviourModule >> contributeIntoUpdate: aUpdate inContext: aContext [
	| commands |
	"Commands first: enqueue lifecycle invocations"
	commands := aContext runCache drainedCommands.
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd contributeLifecycleIntoUpdate: aUpdate inContext: aContext ] ].	
	
	"Invocations second: produce ops"
	aContext runCache lifecycleInvocations
		do: [ :inv | 
			CESimCurrentOrigin
				value: inv
				during: [ inv contributeIntoUpdate: aUpdate inContext: aContext ] ]
]
