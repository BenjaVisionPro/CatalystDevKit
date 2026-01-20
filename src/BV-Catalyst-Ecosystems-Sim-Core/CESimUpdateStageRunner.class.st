Class {
	#name : 'CESimUpdateStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimUpdateStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
	"Subclasses must return a CESimUpdate (or nil)."

	self subclassResponsibility
]

{ #category : 'running' }
CESimUpdateStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| update |
	update := self buildUpdateForStage: aStage inContext: aCESimRunContext.
	aCESimRunContext addUpdate: update.
	^ update
]
