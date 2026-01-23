Class {
	#name : 'CESimInteractionBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'contributing' }
CESimInteractionBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	aSimContext runCache interactionInvocations
		do: [ :invocation | 
			CESimCurrentOrigin
				value: invocation
				during: [ invocation contributeIntoUpdate: aSimUpdate inContext: aSimContext ] ]
]
