"An example provider that fails synchronously to verify delegation diagnostics and cleanup."
Class {
	#name : #BVCFairyFailingProviderStub,
	#superclass : #BVCFairyProviderStub,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #execution }
BVCFairyFailingProviderStub >> sendMessage: aMessage [
	self error: 'Expected child provider failure'
]
