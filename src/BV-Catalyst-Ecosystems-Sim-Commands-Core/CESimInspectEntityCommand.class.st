Class {
	#name : 'CESimInspectEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'capabilities - invocations' }
CESimInspectEntityCommand >> contributeInvocationsInContext: aSimContext update: aSimUpdate [
	aSimContext runCache
		addCapabilityInvocation: (CESimInspectEntityInvocation targetEntityId: targetEntityId)
]

{ #category : 'producing' }
CESimInspectEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #inspectEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]
