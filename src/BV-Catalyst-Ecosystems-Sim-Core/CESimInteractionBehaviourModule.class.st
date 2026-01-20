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

	"Gate: centralised targeting rule (default: must be perceived)."
	(aCESimRunContext canTargetEntityId: entityId)
		ifFalse: [
			"Audit: command was requested but had no eligible target in this bubble this tick."
			aCESimUpdate addEvent: (Dictionary new
				at: #type put: #targetRejected;
				at: #module put: #interaction;
				at: #commandType put: aCommand class name asSymbol;
				at: #entityId put: entityId;
				at: #reason put: #notPerceived;
				at: #tickId put: aCESimRunContext tickId;
				yourself).
			^ self
		].

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