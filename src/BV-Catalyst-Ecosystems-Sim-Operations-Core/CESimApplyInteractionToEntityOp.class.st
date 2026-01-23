Class {
	#name : 'CESimApplyInteractionToEntityOp',
	#superclass : 'CESimEntitySemanticStateOp',
	#instVars : [
		'interactionType',
		'payload',
		'tickId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimApplyInteractionToEntityOp class >> withRegionId: aCERegionId entityId: aCEEntityId interactionType: aType payload: aPayload tickId: aTickId [
	^ (super withRegionId: aCERegionId entityId: aCEEntityId)
		interactionType: aType;
		payload: aPayload;
		tickId: aTickId;
		yourself
]

{ #category : 'applying' }
CESimApplyInteractionToEntityOp >> applyInContext: aCESimRunContext [
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
CESimApplyInteractionToEntityOp >> interactionType: aType [ 
	interactionType := aType 
]

{ #category : 'accessing' }
CESimApplyInteractionToEntityOp >> payload: aPayload [ 
	payload := aPayload 
]

{ #category : 'accessing' }
CESimApplyInteractionToEntityOp >> tickId: aTickId [ 
	tickId := aTickId 
]
