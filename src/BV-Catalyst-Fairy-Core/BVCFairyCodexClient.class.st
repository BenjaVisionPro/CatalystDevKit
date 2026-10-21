"
Barry-local Codex request ownership. Each fresh streaming Zinc client is closed during unwind; consumed response bodies remain inspectable without a live stream. Remove when upstream provides equivalent lifecycle and body evidence guarantees.
"
Class {
	#name : 'BVCFairyCodexClient',
	#superclass : 'GtLOpenAiCodexClient',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'instance creation' }
BVCFairyCodexClient class >> preservingClient: aClient [
	"Retain credentials, configuration and history identity; do not initialize defaults."
	| client |
	self assert: aClient class = GtLOpenAiCodexClient.
	client := self basicNew.
	GtLOpenAiCodexClient allInstVarNames do: [ :slotName |
		client instVarNamed: slotName put: (aClient instVarNamed: slotName) ].
	^ client
]

{ #category : 'requests' }
BVCFairyCodexClient >> post: aPath withEntity: anEntity [
	"Only retry the unfinished model generation. The provider has not received
	this attempt's result, so its tool calls cannot have run."
	^ [ super post: aPath withEntity: anEntity ]
		on: BVCFairyInterruptedCodexStream
		do: [ :interruption |
			[ super post: aPath withEntity: anEntity ]
				on: BVCFairyInterruptedCodexStream
				do: [ :repeatedInterruption |
					repeatedInterruption messageText: 'Codex response was interrupted again after one automatic retry. Both attempts are retained in request history. Completed tools, child results and image changes remain intact; send a follow-up to continue.'.
					repeatedInterruption pass ] ]
]

{ #category : 'requests' }
BVCFairyCodexClient >> postOnce: aPath withEntity: anEntity [
	| httpClient responseBody responseText accumulator requestResponse |
	httpClient := self newStreamingHttpClient.
	^ [
		httpClient url: self baseUrl / aPath.
		httpClient entity: (ZnEntity json: (NeoJSONWriter toString: anEntity)).
		responseBody := httpClient post.
		responseText := self responseStringFrom: responseBody.
		"Retain the consumed body before parsing, including explicit stream errors."
		httpClient response entity: (ZnEntity text: responseText).
		requestResponse := self addHistoryRequestResponse: httpClient.
		accumulator := BVCFairyCodexSseAccumulator new.
		[
			accumulator consume: responseText.
			requestResponse result: accumulator result
		] on: BVCFairyInterruptedCodexStream do: [ :interruption |
			interruption requestResponse: requestResponse.
			interruption pass ].
		requestResponse
	] ensure: [ httpClient close ]
]
