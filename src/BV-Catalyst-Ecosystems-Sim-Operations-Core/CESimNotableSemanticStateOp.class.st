Class {
	#name : 'CESimNotableSemanticStateOp',
	#superclass : 'CESimEntityStateOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'private - state' }
CESimNotableSemanticStateOp >> ensureStateDictInContext: aCESimRunContext [
	| notable state |
	notable := self notableInContext: aCESimRunContext.
	state := notable state.
	state ifNil: [
		state := Dictionary new.
		notable state: state
	].
	^ state
]