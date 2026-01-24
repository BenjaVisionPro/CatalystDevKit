Class {
	#name : 'CESimEntitySemanticStateOp',
	#superclass : 'CESimEntityStateOp',
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'private - state' }
CESimEntitySemanticStateOp >> ensureStateDictInContext: aCESimRunContext [
	| entity state |
	entity := self entityInContext: aCESimRunContext.
	state := entity state.
	state ifNil: [
		state := Dictionary new.
		entity state: state
	].
	^ state
]
