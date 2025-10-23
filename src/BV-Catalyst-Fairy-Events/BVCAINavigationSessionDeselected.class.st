Class {
	#name : #BVCAINavigationSessionDeselected,
	#superclass : #BVCAINavigationSelectionAnnouncement,
	#instVars : [
		'session'
	],
	#category : #'BV-Catalyst-Fairy-Events'
}

{ #category : #accessing }
BVCAINavigationSessionDeselected >> session [
	^ session
]

{ #category : #accessing }
BVCAINavigationSessionDeselected >> session: anObject [
	session := anObject
]
