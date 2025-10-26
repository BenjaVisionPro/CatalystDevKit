Class {
	#name : #BVCAIAssistant,
	#superclass : #GtLlmAssistant,
	#category : #'BV-Catalyst-Fairy-Core-AI'
}

{ #category : #'as yet unclassified' }
BVCAIAssistant >> buildProvider [
	^ connection buildProvider
]

{ #category : #'as yet unclassified' }
BVCAIAssistant >> initialize [
	super initialize.
	connection := nil
]
