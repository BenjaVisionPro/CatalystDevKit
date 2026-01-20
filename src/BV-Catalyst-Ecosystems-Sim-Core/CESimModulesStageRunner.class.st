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

	"Run behaviour modules in the configured order. Each module may:
	 - drain/record command facts (events)
	 - contribute semantic domain ops (entity ops)
	 - optionally emit additional events"
	modules := aCESimRunContext engine behaviour bubbleBehaviourModules.

	modules do: [ :each |
		each produceEventsIntoUpdate: update inContext: aCESimRunContext.
		each produceOperationsIntoUpdate: update inContext: aCESimRunContext
	].

	^ update
]
