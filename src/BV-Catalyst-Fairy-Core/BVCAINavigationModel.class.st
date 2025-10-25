Class {
	#name : #BVCAINavigationModel,
	#superclass : #Object,
	#category : #'BV-Catalyst-Fairy-Core-Navigation'
}

{ #category : #factory }
BVCAINavigationModel class >> null [
	^ BVCAINullNavigationModel default
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> fairyDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedProject [
	<return: #Boolean>
	^ self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedProjectOrSession [
	<return: #Boolean>
	^ self hasSelectedProject or: [ self hasSelectedSession ]
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedSession [
	<return: #Boolean>
	^ self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> isNavigationModel [
	^ true
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> projectsToShow [
	<return: #Collection of: #BVCAIProject>
	^ self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectProject: aProject [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectProjects: aCollectionOfProjects [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectSession: aSession [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectSessions: aCollectionOfSessions [
	self subclassResponsibility
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> selectedProject [
	<return: #Collection of: #BVCAIProject>
	^ self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectedProjectDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> selectedSession [
	<return: #Collection of: #BVCAISession>
	^ self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectedSessionDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> sessionsToShow [
	<return: #Collection of: #BVCAISession>
	^ self subclassResponsibility
]

{ #category : #'api - subscriptions' }
BVCAINavigationModel >> subscribeToSystem [
	"concrete models can subscribe to the system"
]

{ #category : #'api - subscriptions' }
BVCAINavigationModel >> unsubscribeFromSystem [
	"concrete models can unsubscribe from the system"
]
