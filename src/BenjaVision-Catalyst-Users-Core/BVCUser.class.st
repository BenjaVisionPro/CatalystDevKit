Class {
	#name : #BVCUser,
	#superclass : #BVCStoreObject,
	#instVars : [
		'eventLog',
		'friends',
		'messages'
	],
	#category : #'BenjaVision-Catalyst-Users-Core'
}

{ #category : #accessing }
BVCUser >> friends [
	^ friends
]

{ #category : #accessing }
BVCUser >> initialize [
	super initialize.
	eventLog := OrderedCollection new.
	friends := OrderedCollection new.
	messages := OrderedCollection new.
]
