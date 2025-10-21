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

{ #category : #default }
BVCAIFairy class >> default [
	^ singletonInstance ifNil: [ singletonInstance := self new ]
]

{ #category : #default }
BVCAIFairy class >> resetInstance [
	singletonInstance := nil
]

{ #category : #'as yet unclassified' }
BVCAIFairy >> defaultDescription [
	^ 'You are the BVC DevKit Fairy, also knows as Other Barry.'
]

{ #category : #'as yet unclassified' }
BVCAIFairy >> initialize [
	super initialize.
	connection := GtLlmConnectionRegistry uniqueInstance defaultConnection.
	sessions := OrderedCollection new
]
