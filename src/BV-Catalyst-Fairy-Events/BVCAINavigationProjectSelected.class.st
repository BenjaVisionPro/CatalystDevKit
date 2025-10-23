Class {
	#name : #BVCAINavigationProjectSelected,
	#superclass : #BVCAINavigationSelectionAnnouncement,
	#instVars : [
		'project'
	],
	#category : #'BV-Catalyst-Fairy-Events'
}

{ #category : #accessing }
BVCAINavigationProjectSelected >> project [
	^ project
]

{ #category : #accessing }
BVCAINavigationProjectSelected >> project: anObject [
	project := anObject
]
