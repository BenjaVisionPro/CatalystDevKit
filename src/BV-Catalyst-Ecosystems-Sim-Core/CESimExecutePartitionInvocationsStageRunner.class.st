Class {
	#name : 'CESimExecutePartitionInvocationsStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimExecutePartitionInvocationsStageRunner >> buildUpdateForStage: aStage inContext: aContext [
	"I drain my partition's invocation inbox and execute the invocations into a single update."

	| update partition envelopes invocations |
	update := CESimUpdate new.
	partition := aContext subject.

	envelopes := partition invocationInbox drain.

	envelopes
		do: [ :envelope | 
			| invocation |
			invocation := envelope invocation.
			CESimCurrentOrigin
				value: invocation
				during: [ invocation contributeIntoUpdate: update inContext: aContext ] ].	
	
	"Any invocations produced during execution are already in the correct partition context.
	I drain them until quiescent so the tick is explicit and complete."
	invocations := partition drainInvocations.
	[ invocations isEmpty ]
		whileFalse: [ | invocation |
			invocation := invocations removeFirst.
			CESimCurrentOrigin
				value: invocation
				during: [ invocation contributeIntoUpdate: update inContext: aContext ].
			invocations addAll: partition drainInvocations ].

	^ update
]
