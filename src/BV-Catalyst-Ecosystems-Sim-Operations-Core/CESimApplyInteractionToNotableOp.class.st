Class {
	#name : 'CESimApplyInteractionToNotableOp',
	#superclass : 'CESimNotableSemanticStateOp',
	#instVars : [
		'interactionType',
		'payload',
		'tickId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimApplyInteractionToNotableOp class >> withRegionId: aCERegionId entityId: aCEEntityId interactionType: aType payload: aPayload tickId: aTickId [
	^ (super withRegionId: aCERegionId entityId: aCEEntityId)
		interactionType: aType;
		payload: aPayload;
		tickId: aTickId;
		yourself
]

{ #category : 'applying' }
CESimApplyInteractionToNotableOp >> applyInContext: aCESimRunContext [
	| state record |
	state := self ensureStateDictInContext: aCESimRunContext.

	record := Dictionary new
		at: #type put: interactionType;
		at: #payload put: payload;
		at: #tickId put: tickId;
		yourself.

	"v0 semantic state: store the last applied interaction fact."
	state at: #lastInteraction put: record
]

{ #category : 'accessing' }
CESimApplyInteractionToNotableOp >> interactionType: aType [ 
	interactionType := aType 
]

{ #category : 'accessing' }
CESimApplyInteractionToNotableOp >> payload: aPayload [ 
	payload := aPayload 
]

{ #category : 'accessing' }
CESimApplyInteractionToNotableOp >> tickId: aTickId [ 
	tickId := aTickId 
]
