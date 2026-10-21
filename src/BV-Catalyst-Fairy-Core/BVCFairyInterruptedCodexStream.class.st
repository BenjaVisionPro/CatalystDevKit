"
A Codex response ended without a terminal event. Retains the exact HTTP attempt. Only the unfinished model request may be retried; completed tools and image changes are never replayed.
"
Class {
	#name : 'BVCFairyInterruptedCodexStream',
	#superclass : 'Error',
	#instVars : [
		'requestResponse'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyInterruptedCodexStream >> requestResponse [
	^ requestResponse
]

{ #category : 'accessing' }
BVCFairyInterruptedCodexStream >> requestResponse: aRequestResponse [
	requestResponse := aRequestResponse
]
