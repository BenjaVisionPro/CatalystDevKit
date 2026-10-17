"
A local provider for Catalyst Fairy examples. Makes no network calls.
"
Class {
	#name : 'BVCFairyProviderStub',
	#superclass : 'GtLProvider',
	#instVars : [
		'shouldComplete'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'creation' }
BVCFairyProviderStub class >> withDefaultSetup [
	^ self new
]

{ #category : 'accessing' }
BVCFairyProviderStub >> defaultUserMessageClass [
	^ GtLOpenAIUserMessage
]

{ #category : 'initialization' }
BVCFairyProviderStub >> initialize [
	super initialize.
	shouldComplete := true
]

{ #category : 'accessing' }
BVCFairyProviderStub >> modelName [
	^ 'Local example'
]

{ #category : 'execution' }
BVCFairyProviderStub >> sendMessage: aMessage [
	self privateExecutionState: GtLProviderState running.
	shouldComplete ifFalse: [ ^ self ].
	self chat addAssistantMessage: (BVCFairyResponseStub new
		responseModels: (Dictionary new at: 'Markdown' put: (GtLMarkdown content: 'Task complete.'); yourself)).
	self privateExecutionState: GtLProviderState idle.
	self chat announcer announce: GtLThreadRunIsDoneAnnouncement new
]

{ #category : 'accessing' }
BVCFairyProviderStub >> shouldComplete: aBoolean [
	shouldComplete := aBoolean
]
