Class {
	#name : 'CESimRemoveEntityInvocation',
	#superclass : 'CESimLifecycleInvocation',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimRemoveEntityInvocation class >> targetEntityId: anEntityId [
	^ self new
		targetEntityId: anEntityId;
		yourself
]

{ #category : 'as yet unclassified' }
CESimRemoveEntityInvocation >> contributeIntoUpdate: aUpdate inContext: aContext [
	aUpdate
		addEntityOp: (CESimRemoveEntityFromRegionOp
				withRegionId: aContext homeRegionId
				entityId: targetEntityId)
]

{ #category : 'accessing' }
CESimRemoveEntityInvocation >> targetEntityId [
	^ targetEntityId
]

{ #category : 'accessing' }
CESimRemoveEntityInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]
