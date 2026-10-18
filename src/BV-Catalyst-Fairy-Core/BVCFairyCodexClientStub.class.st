"
Controlled request seam for Barry Codex lifecycle examples; never contacts a model.
"
Class {
	#name : 'BVCFairyCodexClientStub',
	#superclass : 'BVCFairyCodexClient',
	#instVars : [
		'httpClient',
		'failHistory'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'testing' }
BVCFairyCodexClientStub >> addHistoryRequestResponse: aClient [
	failHistory == true ifTrue: [ self error: 'Controlled history failure' ].
	^ super addHistoryRequestResponse: aClient
]

{ #category : 'testing' }
BVCFairyCodexClientStub >> failHistory [
	failHistory := true
]

{ #category : 'testing' }
BVCFairyCodexClientStub >> httpClient: aClient [
	httpClient := aClient
]

{ #category : 'testing' }
BVCFairyCodexClientStub >> newStreamingHttpClient [
	^ httpClient isBlock ifTrue: [ httpClient value ] ifFalse: [ httpClient ]
]
