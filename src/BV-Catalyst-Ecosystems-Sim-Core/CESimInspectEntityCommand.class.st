Class {
  #name : 'CESimInspectEntityCommand',
  #superclass : 'CESimPerceptionCommand',
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInspectEntityCommand class >> withTargetEntityId: aCEEntityId [
  ^ self new targetEntityId: aCEEntityId; yourself
]

{ #category : 'producing' }
CESimInspectEntityCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #inspectEntity;
    at: #entityId put: targetEntityId;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]