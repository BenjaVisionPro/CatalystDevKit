Class {
	#name : 'CESimResolveIntentStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimResolveIntentStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
	| commands update |
	commands := aCESimRunContext runCache drainedCommands.

	commands isEmpty ifTrue: [ ^ CESimUpdate new ].

	update := CESimUpdate new.

	commands
		do: [ :cmd | 
			cmd produceEventsIntoUpdate: update inContext: aCESimRunContext.
			aCESimRunContext engine behaviour
				produceOperationsForCommand: cmd
				intoUpdate: update
				inContext: aCESimRunContext ].

	^ update
]
