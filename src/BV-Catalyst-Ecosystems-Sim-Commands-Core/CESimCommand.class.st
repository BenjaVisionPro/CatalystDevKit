Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'capabilities' }
CESimCommand >> contributeInvocationsIntoUpdate: aSimUpdate inContext: aSimContext [
	"Default: this command enqueues no invocations."
	"NoOp"
]

{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aSimUpdate inContext: aSimRunContext [
  "Default: this command emits no events."
	"NoOp"
]
