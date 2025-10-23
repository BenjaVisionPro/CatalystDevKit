Class {
	#name : #BVCAINavigationSessionSelected,
	#superclass : #BVCAINavigationSelectionAnnouncement,
	#instVars : [
		'session',
		'selectedSessions',
		'project'
	],
	#category : #'BV-Catalyst-Fairy-Events'
}

{ #category : #accessing }
BVCAINavigationSessionSelected >> project [
	^ project
]

{ #category : #accessing }
BVCAINavigationSessionSelected >> project: anObject [
	project := anObject
]

{ #category : #accessing }
BVCAINavigationSessionSelected >> selectedSessions [
	^ selectedSessions
]

{ #category : #accessing }
BVCAINavigationSessionSelected >> selectedSessions: anObject [
	selectedSessions := anObject
]

{ #category : #accessing }
BVCAINavigationSessionSelected >> session [
	^ session
]

{ #category : #accessing }
BVCAINavigationSessionSelected >> session: anObject [
	session := anObject
]
