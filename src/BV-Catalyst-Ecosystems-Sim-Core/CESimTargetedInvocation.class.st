Class {
	#name : 'CESimTargetedInvocation',
	#superclass : 'CESimInvocation',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimTargetedInvocation class >> targetEntityId: aCEEntityId [
	^ self new
		targetEntityId: aCEEntityId;
		yourself
]

{ #category : 'accessing' }
CESimTargetedInvocation >> targetEntityId [
	^ targetEntityId
]

{ #category : 'accessing' }
CESimTargetedInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]
