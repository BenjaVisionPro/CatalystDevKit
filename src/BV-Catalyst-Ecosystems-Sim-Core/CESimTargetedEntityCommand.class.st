Class {
  #name : 'CESimTargetedEntityCommand',
  #superclass : 'CESimBubbleCommand',
  #instVars : [ 'targetEntityId' ],
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId [ ^ targetEntityId ]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId: aCEEntityId [ targetEntityId := aCEEntityId ]