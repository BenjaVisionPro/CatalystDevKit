Class {
  #name : 'CESimBubbleCommand',
  #superclass : 'CESimExternalCommand',
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'helpers' }
CESimBubbleCommand >> bubbleInContext: aCESimRunContext [
  ^ aCESimRunContext subject
]

{ #category : 'helpers' }
CESimBubbleCommand >> homeRegionIdInContext: aCESimRunContext [
  ^ (self bubbleInContext: aCESimRunContext) homeRegionId
]