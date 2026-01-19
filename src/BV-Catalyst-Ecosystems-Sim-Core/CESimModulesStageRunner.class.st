Class {
	#name : 'CESimModulesStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimModulesStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
	| update modules |
	update := CESimUpdate new.

	modules := aCESimRunContext engine behaviour bubbleBehaviourModules.

	modules do: [ :each |
		each produceEventsIntoUpdate: update inContext: aCESimRunContext.
		each produceOperationsIntoUpdate: update inContext: aCESimRunContext
	].

	"Publish authoritative tick facts for downstream stages (eg LocalView)."
	aCESimRunContext runCache tickEvents: update events.

	^ update
]