Class {
	#name : 'CESimInspectEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'capabilities - invocations' }
CESimInspectEntityCommand >> contributeInvocationsIntoUpdate: aSimUpdate inContext: aSimContext [
	aSimContext runCache
		addInvocation: (CESimInspectEntityInvocation targetEntityId: targetEntityId)
]

{ #category : 'producing' }
CESimInspectEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #inspectEntityRequested;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]
