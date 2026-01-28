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

{ #category : 'routing' }
CESimTargetedInvocation >> routeOn: anInvocationRouter inContext: aContext [
	"I route using my targetEntityId so I am delivered to the partition that owns my target.
	TODO: When routing must respect playerIntentTickId via historical ownership, route using that tick instead of (or in addition to) current ownership."

	^ anInvocationRouter
		partitionIdsForTargetEntityId: targetEntityId
		inContext: aContext
]

{ #category : 'accessing' }
CESimTargetedInvocation >> targetEntityId [
	^ targetEntityId
]

{ #category : 'accessing' }
CESimTargetedInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]
