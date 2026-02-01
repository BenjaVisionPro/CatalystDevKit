Class {
	#name : 'CRPlacementStrategyConfiguration',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'validation' }
CRPlacementStrategyConfiguration >> validateOn: aValidationResult [
	"Base hook: subclasses may add fields later."
	^ self
]
