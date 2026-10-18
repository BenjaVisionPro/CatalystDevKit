"
Zinc request double. Keeps native Zinc close behavior for optional local socket-resource verification.
"
Class {
	#name : 'BVCFairyCodexHttpClientStub',
	#superclass : 'ZnClient',
	#instVars : [
		'postAction',
		'closeCount'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> close [
	closeCount := self closeCount + 1.
	^ super close
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> closeCount [
	^ closeCount ifNil: [ 0 ]
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> connection: aStream [
	connection := aStream
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> post [
	^ postAction value
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> postAction: aBlock [
	postAction := aBlock
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> response: aResponse [
	response := aResponse
]

{ #category : 'testing' }
BVCFairyCodexHttpClientStub >> upToEnd [
	self error: 'Controlled body-read failure'
]
