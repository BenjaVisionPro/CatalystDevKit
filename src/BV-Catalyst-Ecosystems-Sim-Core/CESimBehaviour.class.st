Class {
	#name : 'CESimBehaviour',
	#superclass : 'Object',
	#instVars : [
		'bubbleBehaviourModules',
		'globalBehaviourModules'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing' }
CESimBehaviour >> bubbleBehaviourModules [
	^ bubbleBehaviourModules
]

{ #category : 'accessing' }
CESimBehaviour >> bubbleBehaviourModules: aCollection [
	bubbleBehaviourModules := aCollection
]

{ #category : 'accessing' }
CESimBehaviour >> globalBehaviourModules [
	^ globalBehaviourModules
]

{ #category : 'accessing' }
CESimBehaviour >> globalBehaviourModules: aCollection [
	globalBehaviourModules := aCollection
]

{ #category : 'initialization' }
CESimBehaviour >> initialize [
	super initialize.

	"Order matters. Keep it explicit and stable."
	bubbleBehaviourModules := OrderedCollection new
		add: CESimCommandInputBehaviourModule new;
		add: CESimLifecycleBehaviourModule new;
		add: CESimStimulusBehaviourModule new;
		add: CESimInteractionBehaviourModule new;
		yourself.

	globalBehaviourModules := OrderedCollection new.
]
