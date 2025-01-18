Class {
	#name : #BVCACFGamePlayTag,
	#superclass : #Object,
	#instVars : [
		'rowName',
		'key',
		'devComment',
		'gamePlayTags'
	],
	#category : #'BV-Catalyst-ACF-Core'
}

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag >> devComment: aString [
	devComment := aString
]

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag >> gamePlayTags [
	^ gamePlayTags
]

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag >> initialize [
	super initialize.
	gamePlayTags := Set new.
]

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag >> key: aString [
	key := aString
]

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag >> rowName: aString [
	rowName := aString
]
