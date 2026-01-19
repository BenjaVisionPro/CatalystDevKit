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

{ #category : 'as yet unclassified' }
CESimCommand >> contributeToStimulusBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: this command has no stimulus contribution."

	"NoOp"

	
]

{ #category : 'contributing' }
CESimCommand >> contributeToLifecycleBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Default: no lifecycle contribution."
	
	"NoOp"
	
	
]

{ #category : 'producing' }
CESimCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  self subclassResponsibility
]