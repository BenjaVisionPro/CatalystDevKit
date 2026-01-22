Class {
	#name : 'CESimInspectEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimInspectEntityCommand class >> withTargetEntityId: aCEEntityId [
  ^ self new targetEntityId: aCEEntityId; yourself
]

{ #category : 'as yet unclassified' }
CESimInspectEntityCommand >> contributeInteractionIntoUpdate: aSimUpdate inContext: aSimContext [
	(self
		canTargetEntityId: targetEntityId
		inContext: aSimContext
		update: aSimUpdate) ifFalse: [ ^ self ].

	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #entityInspected;
				at: #entityId put: targetEntityId;
				at: #snapshot
					put: (aSimContext runCache perceivedVisibleSnapshots
							detect: [ :snap | (snap at: #entityId) = targetEntityId ]
							ifNone: [ Dictionary new
									at: #entityId put: targetEntityId;
									yourself ]);
				at: #tickId put: aSimContext tickId;
				yourself)
]

{ #category : 'producing' }
CESimInspectEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #inspectEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]
