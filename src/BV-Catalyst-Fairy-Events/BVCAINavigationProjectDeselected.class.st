Class {
	#name : #BVCAINavigationProjectDeselected,
	#superclass : #BVCAINavigationSelectionAnnouncement,
	#instVars : [
		'project'
	],
	#category : #'BV-Catalyst-Fairy-Events'
}

{ #category : #accessing }
BVCAINavigationProjectDeselected >> project [
	^ project
]

{ #category : #accessing }
BVCAINavigationProjectDeselected >> project: anObject [
	project := anObject
]
