Class {
	#name : 'CESimSetStateOp',
	#superclass : 'CESimStateOp',
	#instVars : [
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimSetStateOp >> applyInContext: aCESimRunContext [
	(self entityInContext: aCESimRunContext) state: state
]

{ #category : 'accessing' }
CESimSetStateOp >> state: aStateDict [
	state := aStateDict
]
