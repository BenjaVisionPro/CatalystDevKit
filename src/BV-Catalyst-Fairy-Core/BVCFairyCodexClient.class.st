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
BVCFairyCodexClient >> postOnce: aPath withEntity: anEntity [
	| httpClient responseBody responseText accumulator requestResponse |
	httpClient := self newStreamingHttpClient.
	^ [
		httpClient url: self baseUrl / aPath.
		httpClient entity: (ZnEntity json: (NeoJSONWriter toString: anEntity)).
		responseBody := httpClient post.
		responseText := self responseStringFrom: responseBody.
		"Keep the original response and headers, but not its consumed transport stream."
		httpClient response entity: (ZnEntity text: responseText).
		accumulator := GtLOpenAiCodexSseAccumulator new.
		accumulator consume: responseText.
		requestResponse := self addHistoryRequestResponse: httpClient.
		requestResponse result: accumulator result.
		requestResponse
	] ensure: [ httpClient close ]
]
