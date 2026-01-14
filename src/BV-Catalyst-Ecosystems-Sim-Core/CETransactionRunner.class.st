Class {
	#name : 'CETransactionRunner',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CETransactionRunner >> inTransactionDo: aBlock [
	self subclassResponsibility
]
