Class {
	#name : 'CESimTargetedEntityCommand',
	#superclass : 'CESimExternalCommand',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimTargetedEntityCommand class >> targetEntityId: aCEEntityId [
	^ self new
		targetEntityId: aCEEntityId;
		yourself
]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId [ ^ targetEntityId
]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId: aCEEntityId [
	targetEntityId := aCEEntityId
]
