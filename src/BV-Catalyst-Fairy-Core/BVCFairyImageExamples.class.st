"
Focused Barry endpoint serialization checks without UI or network.
"
Class {
	#name : 'BVCFairyImageExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyImageExamples >> cachedImageBytesAreReused [
	<gtExample>
	| view data calls |
	calls := 0.
	view := GtLDataView new imageData png: [ calls := calls + 1. #[1 2 3] ]; yourself.
	view computedImageBytes.
	3 timesRepeat: [
		data := BVCFairyResponsesEndpoint new primitiveDataFor: view.
		self assert: data imageDataBlocks first imageBytes equals: #[1 2 3] ].
	self assert: calls equals: 1.
	^ data
]

{ #category : 'examples' }
BVCFairyImageExamples >> deferredImageIsNeverExecuted [
	<gtExample>
	| view data calls endpoint |
	calls := 0.
	view := GtLDataView new imageData png: [ calls := calls + 1. self error: 'Must not execute' ]; dataKey: 'preview'; yourself.
	endpoint := BVCFairyResponsesEndpoint new.
	3 timesRepeat: [
		data := endpoint primitiveDataFor: view.
		self assert: data imageDataBlocks isEmpty.
		self assert: (data compositeJsonDataBlock serializedJsonString includesSubstring: 'unavailable') ].
	self assert: calls equals: 0.
	^ data
]

{ #category : 'examples' }
BVCFairyImageExamples >> endpointSelectionIsBarryOnly [
	<gtExample>
	| barry ordinary child |
	barry := BVCFairyChat new provider: GtLOpenAiCodexProvider new; yourself.
	ordinary := GtLChat new provider: GtLOpenAiCodexProvider new; yourself.
	self assert: barry provider model userMessageEndpoint class equals: BVCFairyResponsesEndpoint.
	self assert: ordinary provider model userMessageEndpoint class equals: GtLOpenAiCodexResponsesEndpoint.
	child := (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest) createAgentForParent: barry.
	self assert: child provider model userMessageEndpoint class equals: BVCFairyResponsesEndpoint.
	^ child
]

{ #category : 'examples' }
BVCFairyImageExamples >> endpointSerializesNestedToolResult [
	<gtExample>
	| wrapper call output content |
	wrapper := GtLWrappedModel new.
	wrapper instVarNamed: 'cachedMainDataView' put: (self nestedDataViewFor: GtLDataView new).
	call := GtLFunctionToolCall new id: 'barry-image-fixture'; result: wrapper; yourself.
	output := BVCFairyResponsesEndpoint new serializeToolCall: call.
	self assert: (output at: 'call_id') equals: call id.
	content := output at: 'output'.
	self assert: content size equals: 2.
	self assert: (content first at: 'type') equals: 'input_text'.
	self assert: ((content first at: 'text') includesSubstring: 'unavailable').
	self assert: (content second at: 'type') equals: 'input_image'.
	^ output
]

{ #category : 'fixtures' }
BVCFairyImageExamples >> nestedDataViewFor: aView [
	^ GtLDataView new compositeData
		addDataView: (GtLDataView new imageData png: [ self error: 'Deferred nested image executed' ]; yourself);
		addDataView: (GtLDataView new imageData png: #[1 2 3]; yourself);
		yourself
]

{ #category : 'examples' }
BVCFairyImageExamples >> nestedForwardedImagesUseBarryPolicy [
	<gtExample>
	| forwarded data |
	forwarded := GtLDataView new forwardObject object: self; view: #nestedDataViewFor:; yourself.
	data := BVCFairyResponsesEndpoint new primitiveDataFor: forwarded.
	self assert: data imageDataBlocks size equals: 1.
	self assert: (data compositeJsonDataBlock serializedJsonString includesSubstring: 'unavailable').
	^ data
]

{ #category : 'examples' }
BVCFairyImageExamples >> suppliedImageBytesAreSerialized [
	<gtExample>
	| view data |
	view := GtLDataView new imageData png: #[1 2 3]; yourself.
	data := BVCFairyResponsesEndpoint new primitiveDataFor: view.
	self assert: data imageDataBlocks size equals: 1.
	self assert: data imageDataBlocks first imageBytes equals: #[1 2 3].
	self assert: data imageDataBlocks first sourceDataView == view.
	^ data
]
