Class {
	#name : 'CESimPatchNotableStateOp',
	#superclass : 'CESimPatchEntityStateOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimPatchNotableStateOp >> applyInContext: aCESimRunContext [
	| notable |
	notable := self notableInContext: aCESimRunContext.
	self patch keysAndValuesDo: [ :k :v | notable state at: k put: v ]
]
