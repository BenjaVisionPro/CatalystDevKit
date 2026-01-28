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

{ #category : 'routing' }
CESimInvocation >> routeOn: aCESimInvocationRouter inContext: aCESimRunContext [
	"I define routing for invocations. If you are calling me, I must decide which partition(s) should receive me."

	self subclassResponsibility
]

{ #category : 'targeting' }
CESimInvocation >> targetingProfile [
	self subclassResponsibility
]
