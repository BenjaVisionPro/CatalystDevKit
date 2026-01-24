Class {
	#name : 'CESimSetFocusEntityCommand',
	#superclass : 'CESimTargetedEntityCommand',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimSetFocusEntityCommand class >> withTargetEntityId: aCEEntityId [
  ^ self new targetEntityId: aCEEntityId; yourself
]

{ #category : 'as yet unclassified' }
{ #category : 'as yet unclassified' }
{ #category : 'producing' }
CESimSetFocusEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #focusEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]

{ #category : 'contributing' }
CESimSetFocusEntityCommand >> contributeInvocationsIntoUpdate: aUpdate inContext: aContext [
	aContext runCache
		addInvocation: (CESimSetFocusEntityInvocation targetEntityId: targetEntityId)
]
