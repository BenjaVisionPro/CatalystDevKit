"
Barry-only Responses visitor. Retained failures become bounded assistant failure evidence so subsequent requests can continue without deleting errors or replaying completed work. All ordinary messages retain GT serialization.
"
Class {
	#name : 'BVCFairyResponsesMessageVisitor',
	#superclass : 'GtLOpenAiResponsesMessageVisitor',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'visiting' }
BVCFairyResponsesMessageVisitor >> visitGtLErrorMessage: anErrorMessage [
	| message excerpt details text |
	message := anErrorMessage contentText asString.
	excerpt := message first: (message size min: 1024).
	details := { 'kind' -> 'previous_request_failure'.
		'exception' -> anErrorMessage exception class name.
		'message' -> excerpt.
		'truncated' -> (message size > excerpt size) } asDictionary.
	text := 'Previous assistant request failed; acceptance remains unverified. Retained failure evidence: ', (STONJSON toString: details).
	^ { 'role' -> 'assistant'.
		'content' -> { { 'type' -> 'output_text'. 'text' -> text } asDictionary } } asDictionary
]
