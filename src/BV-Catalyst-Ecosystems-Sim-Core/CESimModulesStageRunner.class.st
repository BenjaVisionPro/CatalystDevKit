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
		each contributeIntoUpdate: update inContext: aCESimRunContext
	].

	^ update
]
