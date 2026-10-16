"A local provider for Catalyst Fairy examples. Makes no network calls."
Class {
	#name : #BVCFairyProviderStub,
	#superclass : #GtLProvider,
	#instVars : [
		'shouldComplete'
	],
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #initialization }
BVCFairyProviderStub >> initialize [
	super initialize.
	shouldComplete := true
]

{ #category : #creation }
BVCFairyProviderStub class >> withDefaultSetup [
	^ self new
]

{ #category : #accessing }
BVCFairyProviderStub >> defaultUserMessageClass [
	^ GtLOpenAIUserMessage
]

{ #category : #accessing }
BVCFairyProviderStub >> modelName [
	^ 'Local example'
]

{ #category : #accessing }
BVCFairyProviderStub >> shouldComplete: aBoolean [
	shouldComplete := aBoolean
]

{ #category : #execution }
BVCFairyProviderStub >> sendMessage: aMessage [
	self privateExecutionState: GtLProviderState running.
	shouldComplete ifFalse: [ ^ self ].
	self chat addAssistantMessage: (BVCFairyResponseStub new
		responseModels: (Dictionary new at: 'Markdown' put: (GtLMarkdown content: 'Task complete.'); yourself)).
	self privateExecutionState: GtLProviderState idle.
	self chat announcer announce: GtLlmThreadRunIsDoneAnnouncement new
]
