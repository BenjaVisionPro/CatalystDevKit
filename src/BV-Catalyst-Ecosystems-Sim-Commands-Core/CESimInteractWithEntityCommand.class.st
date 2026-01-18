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
CESimInteractWithEntityCommand >> interactionType: aType [
	interactionType := aType
]

{ #category : 'accessing' }
CESimInteractWithEntityCommand >> payload: aPayload [
	payload := aPayload
]

{ #category : 'producing' }
CESimInteractWithEntityCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| bubble regionId region notable patch newState |

	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #entityInteraction;
		at: #interactionType put: interactionType;
		at: #entityId put: targetEntityId;
		at: #payload put: payload;
		at: #tickId put: aCESimRunContext tickId;
		yourself).

	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.
	region := aCESimRunContext engine ensureRegion: regionId.
	notable := region notableAt: targetEntityId.

	patch := aCESimRunContext engine interactionResolver
		patchForInteractionType: interactionType
		payload: payload
		target: notable
		inContext: aCESimRunContext.

	newState := notable state copy.
	patch keysAndValuesDo: [ :k :v | newState at: k put: v ].

	aCESimUpdate addEntityOp: (CESimSetNotableStateOp
		withRegionId: regionId
		entityId: targetEntityId
		state: newState).
]
