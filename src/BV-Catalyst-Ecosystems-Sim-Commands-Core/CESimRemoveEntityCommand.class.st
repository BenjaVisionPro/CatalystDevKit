Class {
	#name : 'CESimRemoveEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'contributing' }
CESimRemoveEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext subject
		enqueueInvocation: (CESimRemoveEntityInvocation targetEntityId: targetEntityId)
]

{ #category : 'producing' }
CESimRemoveEntityCommand >> produceEventsIntoUpdate: aUpdate inContext: aContext [
	aUpdate
		addEvent: (Dictionary new
				at: #type put: #removeEntityRequested;
				at: #entityId put: targetEntityId;
				at: #tickId put: aContext tickId;
				yourself)
]
