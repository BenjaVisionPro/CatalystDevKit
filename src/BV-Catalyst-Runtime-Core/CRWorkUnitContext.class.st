Class {
	#name : 'CRWorkUnitContext',
	#superclass : 'Dictionary',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'context' }
CRWorkUnitContext >> add: aContextObject [
	self at: aContextObject class put: aContextObject.
	^ aContextObject
]
