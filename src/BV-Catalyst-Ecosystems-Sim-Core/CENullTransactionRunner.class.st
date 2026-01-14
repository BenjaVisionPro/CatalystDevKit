Class {
	#name : 'CENullTransactionRunner',
	#superclass : 'CETransactionRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CENullTransactionRunner >> inTransactionDo: aBlock [
	^ aBlock value
]
