Class {
	#name : 'CESimCommand',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'as yet unclassified' }
CESimCommand >> contributeToInteractionBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no interaction contribution."

	"NoOp"

	
]

{ #category : 'contributing' }
CESimCommand >> contributeToLifecycleBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: no lifecycle contribution."
	
	"NoOp"
	
	
]

{ #category : 'as yet unclassified' }
CESimCommand >> contributeToStimulusBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no stimulus contribution."

	"NoOp"

	
]

{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]

{ #category : 'capabilities' }
CESimCommand >> contributeLifecycleIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no lifecycle capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeStimulusIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no stimulus capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeInteractionIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no interaction capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributePerceptionIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no perception capability contribution."
	"NoOp"
]

{ #category : 'capabilities' }
CESimCommand >> contributeFocusIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no focus capability contribution."
	"NoOp"
]