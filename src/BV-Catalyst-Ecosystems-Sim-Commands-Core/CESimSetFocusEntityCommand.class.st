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
CESimSetFocusEntityCommand >> contributeFocusIntoUpdate: aSimUpdate inContext: aSimContext [
	(self
		canTargetEntityId: targetEntityId
		inContext: aSimContext
		update: aSimUpdate) ifFalse: [ ^ self ].

	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #focusSet;
				at: #entityId put: targetEntityId;
				at: #tickId put: aSimContext tickId;
				yourself)
]

{ #category : 'as yet unclassified' }
CESimSetFocusEntityCommand >> contributePerceptionIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	
]

{ #category : 'producing' }
CESimSetFocusEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #focusEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]
