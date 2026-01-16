Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'producing' }
CESimCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]
