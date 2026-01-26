Class {
	#name : 'CESimInvocation',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'contributing' }
CESimInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	self subclassResponsibility
]

{ #category : 'targeting' }
CESimInvocation >> targetingProfile [
	self subclassResponsibility
]
