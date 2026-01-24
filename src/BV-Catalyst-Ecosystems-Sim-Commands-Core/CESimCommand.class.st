Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'capabilities' }
{ #category : 'capabilities' }
{ #category : 'capabilities' }
CESimCommand >> contributeInvocationsIntoUpdate: aSimUpdate inContext: aSimContext [
	"Default: this command has no invocations capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
{ #category : 'capabilities' }
{ #category : 'capabilities' }
{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]
