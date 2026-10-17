"
A final response for local Catalyst Fairy harness examples.
"
Class {
	#name : 'BVCFairyResponseStub',
	#superclass : 'GtLChatMessage',
	#instVars : [
		'responseModels'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyResponseStub >> responseModels [
	^ responseModels
]

{ #category : 'accessing' }
BVCFairyResponseStub >> responseModels: aDictionary [
	responseModels := aDictionary
]

{ #category : 'accessing' }
BVCFairyResponseStub >> role [
	^ 'assistant'
]
