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

{ #category : 'initialization' }
CESimBehaviour >> initialize [
	super initialize.

	self initializeTargetingPolicies
]

{ #category : 'initialization' }
CESimBehaviour >> initializeTargetingPolicies [
	targetingPolicies := Dictionary new.
	targetingPolicies
		at: CESimTargetingProfile inspect
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new);
		at: CESimTargetingProfile interact
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new);
		at: CESimTargetingProfile targetedStimulus
			put: (OrderedCollection with: CESimPerceivedThisTickTargetingRule new)
]

{ #category : 'as yet unclassified' }
CESimBehaviour >> targetingPolicies [
	^ targetingPolicies ifNil: [ targetingPolicies := Dictionary new ]
]
