Class {
	#name : 'CESimEntitySemanticStateOp',
	#superclass : 'CESimEntityStateOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'private - state' }
CESimEntitySemanticStateOp >> ensureStateDictInContext: aCESimRunContext [
	| notable state |
	notable := self entityInContext: aCESimRunContext.
	state := notable state.
	state ifNil: [
		state := Dictionary new.
		notable state: state
	].
	^ state
]
