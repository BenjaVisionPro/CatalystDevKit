Class {
	#name : 'CESimLifecycleBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
{ #category : 'applying' }
{ #category : 'contributing' }

{ #category : 'contributing' }
CESimLifecycleBehaviourModule >> contributeIntoUpdate: aUpdate inContext: aContext [
	"Invocations only: commands enqueue invocations during command-input."
	aContext runCache lifecycleInvocations
		do: [ :inv |
			CESimCurrentOrigin
				value: inv
				during: [ inv contributeIntoUpdate: aUpdate inContext: aContext ] ]
]
