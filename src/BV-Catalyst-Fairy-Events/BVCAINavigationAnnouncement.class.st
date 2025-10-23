Class {
	#name : #BVCAINavigationAnnouncement,
	#superclass : #Announcement,
	#instVars : [
		'fairy'
	],
	#category : #'BV-Catalyst-Fairy-Events'
}

{ #category : #accessing }
BVCAINavigationAnnouncement >> fairy [
	^ fairy
]

{ #category : #accessing }
BVCAINavigationAnnouncement >> fairy: anObject [
	fairy := anObject
]
