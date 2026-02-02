Class {
	#name : 'CRWorkUnit',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'service context' }
CRWorkUnit class >> requiredWorkerServiceClass [
	"Default: no service context required."

	^ nil
]

{ #category : 'running' }
CRWorkUnit >> executeWorkUnitInContext: aCRWorkUnitExecutionContext [
	"I perform my unit of work. The worker provides execution context."

	self subclassResponsibility
]
