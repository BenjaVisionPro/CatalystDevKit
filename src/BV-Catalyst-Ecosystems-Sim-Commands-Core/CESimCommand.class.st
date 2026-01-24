Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'capabilities' }
CESimCommand >> contributeFocusIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no focus capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeInteractionIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no interaction capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeInvocationsIntoUpdate: aSimUpdate inContext: aSimContext [
	"Default: this command has no invocations capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeLifecycleIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no lifecycle capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributePerceptionIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no perception capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeStimulusIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no stimulus capability contribution."
	"NoOp"
]

{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]
