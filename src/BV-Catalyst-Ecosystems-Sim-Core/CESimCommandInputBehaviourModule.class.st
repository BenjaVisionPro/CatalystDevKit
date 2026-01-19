Class {
	#name : 'CESimCommandInputBehaviourModule',
	#superclass : 'CESimInputBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimCommandInputBehaviourModule >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| bubble commands |
	bubble := aCESimRunContext subject.

	"Assumes bubble understands #drainCommands (your existing convention)."
	commands := bubble drainCommands.

	"Store for downstream modules (single source of truth)."
	aCESimRunContext runCache drainedCommands: commands.

	"Commands own their own event emission."
	commands do: [ :cmd |
		cmd produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext
	]
]
