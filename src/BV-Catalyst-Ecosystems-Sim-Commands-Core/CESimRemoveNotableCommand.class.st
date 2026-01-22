Class {
	#name : 'CESimRemoveNotableCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'as yet unclassified' }
CESimRemoveNotableCommand >> contributeLifecycleIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	(self
		canTargetEntityId: targetEntityId
		inContext: aCESimRunContext
		update: aCESimUpdate) ifFalse: [ ^ self ].

	aCESimUpdate
		addEntityOp: (CESimRemoveNotableFromRegionOp
				withRegionId: aCESimRunContext homeRegionId
				entityId: targetEntityId)
]

{ #category : 'producing' }
CESimRemoveNotableCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Events only."
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #removeNotableRequested;
		at: #entityId put: targetEntityId;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]
