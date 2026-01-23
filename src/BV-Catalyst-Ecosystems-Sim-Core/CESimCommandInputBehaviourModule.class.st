Class {
	#name : 'CESimCommandInputBehaviourModule',
	#superclass : 'CESimInputBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'contributing' }
CESimCommandInputBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| bubble commands |
	bubble := aSimContext subject.	"Assumes bubble understands #drainCommands (your existing convention)."
	commands := bubble drainCommands.	"Store for downstream modules (single source of truth)."
	aSimContext runCache drainedCommands: commands.	"Commands own their own event emission."
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd produceEventsIntoUpdate: aSimUpdate inContext: aSimContext.
					cmd contributeInvocationsIntoUpdate: aSimUpdate inContext: aSimContext ] ]
]
