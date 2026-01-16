Class {
	#name : 'CESimApplyUpdatesStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimApplyUpdatesStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| tickEvents engine |
	aCESimRunContext updates isEmpty ifTrue: [ ^ self ].	
	
	"Preserve events for LocalView before applier clears updates."
	tickEvents := OrderedCollection new.
	aCESimRunContext updates do: [ :u | tickEvents addAll: u events ].
	aCESimRunContext stepCacheAt: #tickEvents put: tickEvents.

	engine := aCESimRunContext engine.
	engine transactionRunner
		inTransactionDo: [ engine updateApplier applyUpdatesInContext: aCESimRunContext ]
]
