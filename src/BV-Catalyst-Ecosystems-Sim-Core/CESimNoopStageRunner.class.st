Class {
	#name : 'CESimNoopStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimNoopStageRunner >> runStage: aStage inContext: aCESimRunContext [
	^ aCESimRunContext
]
