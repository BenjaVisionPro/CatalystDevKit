Class {
	#name : 'CESimModulesStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimModulesStageRunner >> buildUpdateForStage: aStage inContext: aContext [
	| update commands |

	update := CESimUpdate new.

	"Explicit, destructive drain of external command input"
	commands := aContext subject drainCommands.

	self
		processCommands: commands
		intoUpdate: update
		inContext: aContext.

	^ update
]

{ #category : 'running' }
CESimModulesStageRunner >> processCommands: commands intoUpdate: anUpdate inContext: aContext [
	| subject invocations |
	subject := aContext subject.
	
	"Phase 1 — commands (enqueue invocations + emit events)"
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd contributeInvocationsIntoUpdate: anUpdate inContext: aContext.
					cmd produceEventsIntoUpdate: anUpdate inContext: aContext ] ].	

	"Phase 2+ — invocations until quiescent (produce ops/events; may enqueue more invocations)"
	invocations := subject drainInvocations.
	[ invocations isEmpty ]
		whileFalse: [ | invocation |
			invocation := invocations removeFirst.

			CESimCurrentOrigin
				value: invocation
				during: [ invocation contributeIntoUpdate: anUpdate inContext: aContext ].

			invocations addAll: subject drainInvocations ]
]
