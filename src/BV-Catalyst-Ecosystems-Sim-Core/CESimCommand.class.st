Class {
  #name : 'CESimCommand',
  #superclass : 'Object',
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]