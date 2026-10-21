"
Barry-only classification of interrupted Codex responses. Reuses GT parsing and output construction; does not interpret partial function calls as completed output.
"
Class {
	#name : 'BVCFairyCodexSseAccumulator',
	#superclass : 'GtLOpenAiCodexSseAccumulator',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyCodexSseAccumulator >> result [
	(events anySatisfy: [ :event | (event at: 'type' ifAbsent: [ '' ]) = 'error' ]) ifTrue: [
		self error: 'Codex returned a stream error. The response is retained in request history.' ].
	terminalResponse ifNil: [
		BVCFairyInterruptedCodexStream signal: 'Codex response ended before completion. The HTTP attempt is retained; partial tool arguments were not executed.' ].
	^ super result
]
