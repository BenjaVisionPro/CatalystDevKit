Class {
	#name : 'CESimApplyUpdatesStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimApplyUpdatesStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| engine tickEvents |
	engine := aCESimRunContext engine.

	"Capture tick events before updates are cleared."
	tickEvents := OrderedCollection new.
	aCESimRunContext updates do: [ :eachUpdate |
		tickEvents addAll: eachUpdate events
	].
	aCESimRunContext runCache tickEvents: tickEvents.

	aCESimRunContext updates isEmpty ifTrue: [ ^ self ].

	engine transactionRunner inTransactionDo: [
		engine updateApplier applyUpdatesInContext: aCESimRunContext
	].
]
