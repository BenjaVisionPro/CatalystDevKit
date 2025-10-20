Class {
	#name : #BVCDevKitFairy,
	#superclass : #GtLlmAssistant,
	#instVars : [
		'chat',
		'plannerAssistant',
		'groundingAssistant',
		'codegenAssistant',
		'verifierAssistant',
		'sessionStore'
	],
	#category : #'BV-Catalyst-Fairy-AI'
}

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> buildProvider [
  | p |
  p := GtOpenAIResponseProvider withApiKeyFromFile.
  p model: self defaultModelName.
  ^ p
]

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> chat [
	^ chat
		ifNil: [ chat := self createChat.
			self registerDefaultToolsOn: chat.
			chat ]
]

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> defaultDescription [
	^ 'You are the BVC DevKit Fairy, also knows as Other Barry. Evidence-lock only: every API used in generated C++ must have a {spaceId:path#Lx-Ly} or a pinned doc anchor. No guessing. Only drop-in files/structured patches on a feature branch. After each change: build with UBT, parse diagnostics, propose minimal fixes, iterate until green.'
]

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> defaultModelName [
  ^ 'gpt-5'
]

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> ensureChat [
  chat ifNotNil: [ ^ chat ].
  chat := self createChat.          "GtLlmAssistant>>createChat"
  self registerDefaultToolsOn: chat.
  ^ chat

]

{ #category : #'as yet unclassified' }
BVCDevKitFairy >> initialize [
    super initialize.

]
