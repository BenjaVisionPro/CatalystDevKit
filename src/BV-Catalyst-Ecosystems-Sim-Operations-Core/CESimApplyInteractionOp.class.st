Class {
	#name : 'CESimApplyInteractionOp',
	#superclass : 'CESimStateOp',
	#instVars : [
		'interactionType',
		'payload',
		'tickId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimApplyInteractionOp >> applyInContext: aCESimRunContext [
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
CESimApplyInteractionOp >> interactionType: aType [ 
	interactionType := aType 
]

{ #category : 'accessing' }
CESimApplyInteractionOp >> payload: aPayload [ 
	payload := aPayload 
]

{ #category : 'accessing' }
CESimApplyInteractionOp >> tickId: aTickId [ 
	tickId := aTickId 
]
