Class {
	#name : 'CESimInteractionBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'contributing' }
CESimInteractionBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| commands |
	"Command contributions (may enqueue interaction invocations for this tick)"
	commands := aSimContext runCache drainedCommands.
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd contributeInteractionIntoUpdate: aSimUpdate inContext: aSimContext ] ].	
	
	"Capability invocations - execute after commands"
	aSimContext runCache interactionInvocations
		do: [ :invocation | 
			CESimCurrentOrigin
				value: invocation
				during: [ invocation contributeIntoUpdate: aSimUpdate inContext: aSimContext ] ]
]
