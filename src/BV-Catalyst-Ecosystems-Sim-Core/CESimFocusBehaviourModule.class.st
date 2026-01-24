Class {
	#name : 'CESimFocusBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'contributing' }
CESimFocusBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	"Invocations only: commands enqueue invocations during command-input."
	aSimContext runCache focusInvocations
		do: [ :invocation |
			CESimCurrentOrigin value: invocation during: [
				invocation contributeIntoUpdate: aSimUpdate inContext: aSimContext
			]
		]
]
