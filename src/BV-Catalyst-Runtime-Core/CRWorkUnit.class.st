Class {
	#name : 'CRWorkUnit',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'running' }
CRWorkUnit >> run [
	"I perform my unit of work."

	self subclassResponsibility
]
