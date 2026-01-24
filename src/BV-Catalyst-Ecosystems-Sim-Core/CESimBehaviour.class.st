Class {
	#name : 'CESimBehaviour',
	#superclass : 'Object',
	#instVars : [
		'bubbleBehaviourModules',
		'globalBehaviourModules',
		'targetingPolicies'
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

	self
		initializeGlobalBehaviour;
		initializeBubbleBehaviour;
		initializeTargetingPolicies
]

{ #category : 'initialization' }
CESimBehaviour >> initializeBubbleBehaviour [
	"Order matters. Keep it explicit and stable."

	bubbleBehaviourModules := OrderedCollection new
			add: CESimCommandInputBehaviourModule new;
			add: CESimLifecycleBehaviourModule new;
			add: CESimFocusBehaviourModule new;
			add: CESimStimulusBehaviourModule new;
			add: CESimInteractionBehaviourModule new;
			yourself
]

{ #category : 'initialization' }
CESimBehaviour >> initializeGlobalBehaviour [
	globalBehaviourModules := OrderedCollection new
]

{ #category : 'initialization' }
CESimBehaviour >> initializeTargetingPolicies [
	targetingPolicies := Dictionary new.
	targetingPolicies
		at: CESimTargetingProfile inspect
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new);
		
		at: CESimTargetingProfile focus put: (targetingPolicies at: CESimTargetingProfile inspect);
		at: CESimTargetingProfile interact
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new);
		at: CESimTargetingProfile targetedStimulus
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new)
]

{ #category : 'as yet unclassified' }
CESimBehaviour >> targetingPolicies [
	^ targetingPolicies ifNil: [ targetingPolicies := Dictionary new ]
]
