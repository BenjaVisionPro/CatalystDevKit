Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
{ #category : 'contributing' }

{ #category : 'contributing' }
CESimStimulusBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	"Invocations only: commands enqueue invocations during command-input."
	aSimContext runCache stimulusInvocations
		do: [ :invocation |
			CESimCurrentOrigin value: invocation during: [
				invocation contributeIntoUpdate: aSimUpdate inContext: aSimContext
			]
		]
]
