Class {
	#name : 'CESimInteractWithCreatureCommand',
	#superclass : 'CESimCreatureInteractionCommand',
	#instVars : [
		'interactionType',
		'payload'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimInteractWithCreatureCommand class >> withTargetEntityId: aCEEntityId type: anInteractionType payload: aPayload [
  ^ self new
    targetEntityId: aCEEntityId;
    interactionType: anInteractionType;
    payload: aPayload;
    yourself
]

{ #category : 'accessing' }
CESimInteractWithCreatureCommand >> interactionType: aType [ interactionType := aType
]

{ #category : 'accessing' }
CESimInteractWithCreatureCommand >> payload: aPayload [ payload := aPayload
]

{ #category : 'producing' }
CESimInteractWithCreatureCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #creatureInteraction;
    at: #interactionType put: interactionType;
    at: #entityId put: targetEntityId;
    at: #payload put: payload;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]
