Class {
	#name : 'CESimInteractWithEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
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

{ #category : 'as yet unclassified' }
CESimInteractWithEntityCommand >> contributeInteractionIntoUpdate: aSimUpdate inContext: aSimContext [
	(self
		canTargetEntityId: targetEntityId
		inContext: aSimContext
		update: aSimUpdate) ifFalse: [ ^ self ].

	aSimUpdate
		addEntityOp: (CESimApplyInteractionToNotableOp
				withRegionId: aSimContext subject homeRegionId
				entityId: targetEntityId
				interactionType: self interactionType
				payload: self payload
				tickId: aSimContext tickId)
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
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #entityInteraction;
		at: #interactionType put: interactionType;
		at: #entityId put: targetEntityId;
		at: #payload put: payload;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]
