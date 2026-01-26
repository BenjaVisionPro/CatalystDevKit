Class {
	#name : 'CESimInteractWithEntityInvocation',
	#superclass : 'CESimInteractionInvocation',
	#instVars : [
		'targetEntityId',
		'interactionType',
		'payload'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInteractWithEntityInvocation class >> targetEntityId: aCEEntityId interactionType: aType payload: aPayload [
	^ self new
		targetEntityId: aCEEntityId;
		interactionType: aType;
		payload: aPayload;
		yourself
]

{ #category : 'as yet unclassified' }
CESimInteractWithEntityInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	(aSimContext
		canTargetEntityId: targetEntityId
		invocation: self
		update: aSimUpdate) ifFalse: [ ^ self ].

	aSimUpdate
		addEntityOp: (CESimApplyInteractionOp
				withRegionId: aSimContext partitionId
				entityId: targetEntityId
				interactionType: interactionType
				payload: payload
				tickId: aSimContext tickId)
]

{ #category : 'accessing' }
CESimInteractWithEntityInvocation >> interactionType: anObject [
	interactionType := anObject
]

{ #category : 'accessing' }
CESimInteractWithEntityInvocation >> payload: anObject [
	payload := anObject
]

{ #category : 'accessing' }
CESimInteractWithEntityInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]

{ #category : 'targeting' }
CESimInteractWithEntityInvocation >> targetingProfile [
	^ CESimTargetingProfile interact
]
