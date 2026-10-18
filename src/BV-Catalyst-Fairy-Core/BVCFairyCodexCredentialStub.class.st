"
Offline credential refresh counter. Holds no credentials and never contacts OAuth.
"
Class {
	#name : 'BVCFairyCodexCredentialStub',
	#superclass : 'Object',
	#instVars : [
		'refreshCount'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'testing' }
BVCFairyCodexCredentialStub >> isExpired [
	^ false
]

{ #category : 'testing' }
BVCFairyCodexCredentialStub >> refresh [
	refreshCount := self refreshCount + 1.
	^ self
]

{ #category : 'testing' }
BVCFairyCodexCredentialStub >> refreshCount [
	^ refreshCount ifNil: [ 0 ]
]
