Class {
	#name : #BVCAIAssistant,
	#superclass : #GtLlmAssistant,
	#category : #'BV-Catalyst-Fairy-Core-AI'
}

{ #category : #'as yet unclassified' }
BVCAIAssistant >> buildProvider [
  | p |
  p := GtOpenAIResponseProvider withApiKeyFromFile.
  p model: self defaultModelName.
  ^ p
]

{ #category : #'as yet unclassified' }
BVCAIAssistant >> defaultModelName [
  ^ 'gpt-5'
]

{ #category : #'as yet unclassified' }
BVCAIAssistant >> initialize [
	super initialize.
	connection := nil
]
