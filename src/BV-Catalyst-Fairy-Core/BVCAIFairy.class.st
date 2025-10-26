Class {
	#name : #BVCAIFairy,
	#superclass : #BVCAIAssistant,
	#instVars : [
		'chat',
		'sessions'
	],
	#classVars : [
		'singletonInstance'
	],
	#category : #'BV-Catalyst-Fairy-Core-AI'
}

{ #category : #'as yet unclassified' }
BVCAIFairy >> defaultDescription [
	^ 'You are the BVC DevKit Fairy, also known as Other Barry.'
]

{ #category : #'as yet unclassified' }
BVCAIFairy >> initialize [
	super initialize.
	connection := GtLlmConnectionRegistry uniqueInstance defaultConnection.
	sessions := OrderedCollection new
]
