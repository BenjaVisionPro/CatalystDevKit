Class {
	#name : 'CESimStageRunner',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimStageRunner >> runStage: aStage inContext: aCESimRunContext [
	self subclassResponsibility
]
