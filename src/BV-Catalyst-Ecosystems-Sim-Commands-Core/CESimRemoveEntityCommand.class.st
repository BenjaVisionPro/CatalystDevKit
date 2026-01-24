Class {
	#name : 'CESimRemoveEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'as yet unclassified' }
CESimRemoveEntityCommand >> contributeLifecycleIntoUpdate: aUpdate inContext: aContext [
	aContext runCache
		addInvocation: (CESimRemoveEntityInvocation targetEntityId: targetEntityId)
]

{ #category : 'producing' }
CESimRemoveEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Events only."
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #removeNotableRequested;
		at: #entityId put: targetEntityId;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]
