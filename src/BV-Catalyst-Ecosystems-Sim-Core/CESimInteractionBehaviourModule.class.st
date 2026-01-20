Class {
	#name : 'CESimInteractionBehaviourModule',
	#superclass : 'CESimTargetedEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimInteractionBehaviourModule >> applyInteractionCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId entityId |
	regionId := self homeRegionIdInContext: aCESimRunContext.
	entityId := aCommand targetEntityId.

	"Gate: only interact with entities currently perceived by this bubble."
	((aCESimRunContext runCache perceivedVisibleSnapshots) anySatisfy: [ :snap | (snap at: #entityId) = entityId ])
		ifFalse: [ ^ self ].

	aCESimUpdate
		addEntityOp: (CESimApplyInteractionToNotableOp
				withRegionId: regionId
				entityId: entityId
				interactionType: aCommand interactionType
				payload: aCommand payload
				tickId: aCESimRunContext tickId)
]

{ #category : 'producing' }
CESimInteractionBehaviourModule >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| commands |
	commands := aCESimRunContext runCache drainedCommands.

	commands
		do: [ :cmd | 
			cmd
				contributeToInteractionBehaviourModule: self
				intoUpdate: aCESimUpdate
				inContext: aCESimRunContext ]
]
