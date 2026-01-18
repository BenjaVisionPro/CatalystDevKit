Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]

{ #category : 'producing' }
CESimCommand >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  "Default no op"
]
