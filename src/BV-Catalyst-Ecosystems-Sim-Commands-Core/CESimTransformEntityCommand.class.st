Class {
	#name : 'CESimTransformEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#instVars : [
		'transform'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimTransformEntityCommand class >> targetEntityId: anEntityId transform: aTransform [
	^ self new
		targetEntityId: anEntityId;
		transform: aTransform;
		yourself
]

{ #category : 'as yet unclassified' }
CESimTransformEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext
		enqueueInvocation: (CESimTransformEntityInvocation
				targetEntityId: targetEntityId
				transform: transform)
]

{ #category : 'as yet unclassified' }
CESimTransformEntityCommand >> produceEventsIntoUpdate: anUpdate inContext: aContext [
	anUpdate
		addEvent: (Dictionary new
				at: #type put: #transformEntityRequested;
				at: #entityId put: targetEntityId;
				at: #transform put: transform;
				at: #tickId put: aContext tickId;
				yourself)
]

{ #category : 'accessing' }
CESimTransformEntityCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimTransformEntityCommand >> transform: anObject [
	transform := anObject
]
