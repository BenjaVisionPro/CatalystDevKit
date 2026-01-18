Class {
	#name : 'CESimInteractWithEntityCommand',
	#superclass : 'CESimEntityInteractionCommand',
	#instVars : [
		'interactionType',
		'payload'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimInteractWithEntityCommand class >> withTargetEntityId: aCEEntityId type: anInteractionType payload: aPayload [
  ^ self new
    targetEntityId: aCEEntityId;
    interactionType: anInteractionType;
    payload: aPayload;
    yourself
]

{ #category : 'accessing' }
CESimInteractWithEntityCommand >> interactionType [
	^ interactionType
]

{ #category : 'accessing' }
CESimInteractWithEntityCommand >> interactionType: aType [
	interactionType := aType
]

{ #category : 'accessing' }
CESimInteractWithEntityCommand >> payload [
	^ payload
]

{ #category : 'accessing' }
CESimInteractWithEntityCommand >> payload: aPayload [
	payload := aPayload
]

{ #category : 'producing' }
CESimInteractWithEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate
		addEvent: (Dictionary new
				at: #type put: #entityInteraction;
				at: #interactionType put: interactionType;
				at: #entityId put: targetEntityId;
				at: #payload put: payload;
				at: #tickId put: aCESimRunContext tickId;
				yourself)
]

{ #category : 'producing' }
CESimInteractWithEntityCommand >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| bubble regionId engine region notable patch |
	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.

	engine := aCESimRunContext engine.
	region := engine ensureRegion: regionId.

	notable := region notableAt: self targetEntityId.

	patch := engine interactionResolver
			patchForInteractionType: self interactionType
			payload: self payload
			target: notable
			inContext: aCESimRunContext.

	aCESimUpdate
		addEntityOp: (CESimPatchNotableStateOp
				withRegionId: regionId
				entityId: self targetEntityId
				patch: patch)
]
