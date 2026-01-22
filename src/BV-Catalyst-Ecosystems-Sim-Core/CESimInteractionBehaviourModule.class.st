Class {
	#name : 'CESimInteractionBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimInteractionBehaviourModule >> applyInspectEntityCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| entityId snapshot |
	entityId := aCommand targetEntityId.

	(self
		gateTargetEntityId: entityId
		forCommand: aCommand
		module: #interaction
		intoUpdate: aCESimUpdate
		inContext: aCESimRunContext) ifFalse: [ ^ self ].	
		
	"This emits #targetRejected centrally."	"Success: include the perceived snapshot deterministically (read-only inspect)."
	snapshot := (self perceivedVisibleSnapshotsInContext: aCESimRunContext)
			detect: [ :snap | (snap at: #entityId) = entityId ]
			ifNone: [ nil ].

	aCESimUpdate
		addEvent: (Dictionary new
				at: #type put: #entityInspected;
				at: #entityId put: entityId;
				at: #snapshot put: snapshot;
				at: #tickId put: aCESimRunContext tickId;
				yourself)
]

{ #category : 'producing' }
CESimInteractionBehaviourModule >> applyInteractionCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId entityId |
	regionId := self homeRegionIdInContext: aCESimRunContext.
	entityId := aCommand targetEntityId.

	(self
		gateTargetEntityId: entityId
		forCommand: aCommand
		module: #interaction
		intoUpdate: aCESimUpdate
		inContext: aCESimRunContext) ifFalse: [ ^ self ].

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
		do: [ :cmd | cmd contributeInteractionIntoUpdate: aCESimUpdate inContext: aCESimRunContext ]
]
