Class {
	#name : 'CESimTargetedEntityCommand',
	#superclass : 'CESimBubbleCommand',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId [ ^ targetEntityId
]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId: aCEEntityId [ targetEntityId := aCEEntityId
]
