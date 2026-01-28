Class {
	#name : 'CESimExecuteCommandInputStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimExecuteCommandInputStageRunner >> buildUpdateForStage: aStage inContext: aContext [
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

{ #category : 'routing' }
CESimExecuteCommandInputStageRunner >> envelopeForInvocation: anInvocation sequence: anInteger inContext: aContext [
	"I wrap an invocation in an envelope so it can be delivered to partition inboxes.
	TODO: Replace the sequence-based invocationId with a real, stable invocation id derived from player intent / client command identity."

	^ CESimInvocationEnvelope new
		invocationId: anInteger;
		bubbleId: aContext subject bubbleId;
		gatewayId: nil;
		playerIntentTickId: aContext tickId;
		invocation: anInvocation;
		yourself
]

{ #category : 'routing' }
CESimExecuteCommandInputStageRunner >> invocationRouterInContext: aContext [
	"I answer a router for this tick. I cache it in the runCache so routing is consistent and cheap within the tick."

	^ aContext
		runCacheAt: #invocationRouter
		ifAbsent: [ | router |
			router := CESimInvocationRouter
					entityDirectory: CESimEntityDirectory new
					partitionMap: CESimPartitionMap new.
			aContext runCacheAt: #invocationRouter put: router.
			router ]
]

{ #category : 'running' }
CESimExecuteCommandInputStageRunner >> processCommands: commands intoUpdate: anUpdate inContext: aContext [
	| subject invocations invocationSequence router |
	subject := aContext subject.
	router := self invocationRouterInContext: aContext.	
	
	"Phase 1 — commands (enqueue invocations + emit events)"
	commands
		do: [ :cmd | 
			CESimCurrentOrigin
				value: cmd
				during: [ cmd contributeInvocationsIntoUpdate: anUpdate inContext: aContext.
					cmd produceEventsIntoUpdate: anUpdate inContext: aContext ] ].	
	
	"Phase 2+ — drain invocations until quiescent and route them to partition inboxes."
	invocationSequence := 0.
	invocations := subject drainInvocations.

	[ invocations isEmpty ]
		whileFalse: [ | invocation envelope |
			invocation := invocations removeFirst.
			invocationSequence := invocationSequence + 1.

			envelope := self
					envelopeForInvocation: invocation
					sequence: invocationSequence
					inContext: aContext.

			router route: envelope inContext: aContext.

			invocations addAll: subject drainInvocations ]
]
