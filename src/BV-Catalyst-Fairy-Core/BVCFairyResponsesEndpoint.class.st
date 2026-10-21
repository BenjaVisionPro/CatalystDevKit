"
Barry-only Responses endpoint policy. Preserves native data-view serialization but never starts lazy image computations. Supplied/cached image bytes are sent as image content; deferred images produce explicit text evidence. GT/Pharo only.
"
Class {
	#name : 'BVCFairyResponsesEndpoint',
	#superclass : 'GtLOpenAiCodexResponsesEndpoint',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'serialization' }
BVCFairyResponsesEndpoint >> newMessageVisitor [
	^ BVCFairyResponsesMessageVisitor new
]

{ #category : 'serialization' }
BVCFairyResponsesEndpoint >> primitiveDataFor: aDataView [
	| builder |
	builder := GtLPrimitiveMessageDataBuilder new sourceDataView: aDataView; yourself.
	self serializeDataView: aDataView on: builder.
	^ builder messageDataBlock
]

{ #category : 'serialization' }
BVCFairyResponsesEndpoint >> serializeDataView: aDataView on: aBuilder [
	"Select at the consumer boundary; never invoke a lazy image renderer. Forwarded views keep their existing target cache."
	(aDataView isKindOf: GtLImageDataView) ifTrue: [
		| bytes |
		bytes := aDataView instVarNamed: 'computedImageBytes'.
		bytes ifNil: [
			bytes := aDataView instVarNamed: 'imageBytesComputation'.
			(bytes isKindOf: ByteArray) ifFalse: [ bytes := nil ] ].
		bytes ifNil: [
			^ aBuilder addJsonDataBlockFor: ({ 'imageStatus' -> 'unavailable'.
				'reason' -> 'Barry does not execute deferred image computations during tool serialization.' } asDictionary)
				dataKey: aDataView dataKey from: aDataView ].
		^ aBuilder addImageBlockFor: bytes type: aDataView imageType label: aDataView computeContentLabel dataKey: aDataView dataKey from: aDataView ].
	(aDataView isKindOf: GtLForwardDataView) ifTrue: [
		^ self serializeDataView: aDataView targetDataView on: aBuilder ].
	(aDataView isKindOf: GtLCompositeDataView) ifTrue: [
		^ aDataView isWithArraySerialization
			ifTrue: [ aBuilder forArrayWithDataKey: aDataView dataKey do: [ aDataView dataViews do: [ :view | self serializeDataView: view on: aBuilder ] ] ]
			ifFalse: [ aBuilder forDataKey: aDataView dataKey do: [ aDataView dataViews do: [ :view | self serializeDataView: view on: aBuilder ] ] ] ].
	^ aDataView serializeToLlmPrimiteDataOn: aBuilder
]

{ #category : 'serialization' }
BVCFairyResponsesEndpoint >> serializeToolCall: aToolCall [
	| data output |
	data := self primitiveDataFor: aToolCall result mainDataView.
	output := OrderedCollection with: ({ 'type' -> 'input_text'. 'text' -> data compositeJsonDataBlock serializedJsonString } asDictionary).
	data imageDataBlocks do: [ :image | output addAll: image serializeForOpenAI ].
	^ { 'type' -> 'function_call_output'. 'call_id' -> aToolCall id. 'output' -> output asArray } asDictionary
]
