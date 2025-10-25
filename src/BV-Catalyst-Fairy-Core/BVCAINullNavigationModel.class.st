Class {
	#name : #BVCAINullNavigationModel,
	#superclass : #BVCAINavigationModel,
	#traits : 'TGtUniqueInstance',
	#classTraits : 'TGtUniqueInstance classTrait',
	#category : #'BV-Catalyst-Fairy-Core-Navigation'
}

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> fairyDo: aBlock [
	"do nothing"
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> hasSelectedProject [
	^ false
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> hasSelectedSession [
	^ false
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> isNavigationModel [
	^ false
]

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> projectsToShow [
	^ #()
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectProject: aProject [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectProjects: aCollectionOfProjects [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectSession: aSession [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectSessions: aCollectionOfSessions [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectedProjectDo: aBlock [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectedSessionDo: aBlock [
	"do nothing"
]

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> sessionsToShow [
	^ #()
]
