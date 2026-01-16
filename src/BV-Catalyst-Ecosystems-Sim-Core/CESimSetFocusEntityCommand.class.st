Class {
  #name : 'CESimSetFocusEntityCommand',
  #superclass : 'CESimPerceptionCommand',
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimSetFocusEntityCommand class >> withTargetEntityId: aCEEntityId [
  ^ self new targetEntityId: aCEEntityId; yourself
]

{ #category : 'producing' }
CESimSetFocusEntityCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #focusEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]