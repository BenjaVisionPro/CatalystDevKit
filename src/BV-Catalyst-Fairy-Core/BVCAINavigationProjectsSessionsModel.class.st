Class {
	#name : #BVCAINavigationProjectsSessionsModel,
	#superclass : #BVCAINavigationModel,
	#traits : 'TGtAnnouncer',
	#classTraits : 'TGtAnnouncer classTrait',
	#instVars : [
		'announcer',
		'coder',
		'fairy',
		'selectedProject',
		'selectedSession',
		'selectedPackage',
		'selectedTag',
		'selectedProtocol',
		'selectedMethod',
		'selectedSlot',
		'selectedClass',
		'needsUpdate',
		'performingBulkChanges',
		'selectedMethods',
		'selectedClasses',
		'selectedSessions'
	],
	#category : #'BV-Catalyst-Fairy-Core-Navigation'
}

{ #category : #announcer }
BVCAINavigationProjectsSessionsModel >> announcer [
	^ announcer ifNil: [ announcer := Announcer new ]
]

{ #category : #asserting }
BVCAINavigationProjectsSessionsModel >> assertFairy: aFairy [
	self 
		assert: [ aFairy isNotNil ]
		description: [ 'Fairy must be non-nil' ].
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> deselectProject [
	"Deselect anything downstream"

	self privateJustDeselectProject ifFalse: [ ^ self ].
	
	self deselectSession.
	self notifySessionsToShowChanged
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> deselectSession [
	"Deselect anything downstream"

	self privateJustDeselectSession ifFalse: [ ^ self ]
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> fairy: aFairy [
	(self setFairy: aFairy)
		ifFalse: [ ^ self ].

	self notifyFairyChanged
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> fairyDo: aBlock [
	fairy ifNotNil: aBlock
]

{ #category : #'api - testing' }
BVCAINavigationProjectsSessionsModel >> hasSelectedProject [
	<return: #Boolean>
	^ self selectedProject notNil
]

{ #category : #'api - testing' }
BVCAINavigationProjectsSessionsModel >> hasSelectedSession [
	<return: #Boolean>
	^ self selectedSession isNotNil
]

{ #category : #initialization }
BVCAINavigationProjectsSessionsModel >> initialize [
	super initialize.
	needsUpdate := false.
	performingBulkChanges := false.
	self fairy: GtPharoPackagesCoder forAllPackages
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyFairyChanged [
	self announce: (BVCAINavigationFairyChanged new fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectDeselected: aPreviouslySelectedProject [
	self
		announce: (BVCAINavigationProjectDeselected new
				project: aPreviouslySelectedProject;
				fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectSelected: aProject [
	self
		announce: (BVCAINavigationProjectSelected new
				fairy: fairy;
				project: aProject)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectsToShowChanged [
	self announce: (BVCAINavigationProjectsToShowChanged new fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionDeselected: aPreviouslySelectedSession [
	self
		announce: (BVCAINavigationSessionDeselected new
				session: aPreviouslySelectedSession;
				fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionSelected: aSession [
	self
		announce:
			(BVCAINavigationSessionSelected new
				fairy: fairy;
				project: selectedProject;
				session: aSession;
				selectedSessions: self selectedSessions)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionSelected: aSession project: aProject [
	self
		announce: (BVCAINavigationSessionSelected new
				fairy: fairy;
				project: aProject;
				session: aSession;
				selectedSessions: self selectedSessions)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionsToShowChanged [
	self announce: (BVCAINavigationSessionsToShowChanged new fairy: fairy)
]

{ #category : #'api - subscriptions' }
BVCAINavigationProjectsSessionsModel >> onAboutToPerformBulkChanges: anAnnouncement [
	performingBulkChanges := true.
	needsUpdate := false
]

{ #category : #'private - announcement handling' }
BVCAINavigationProjectsSessionsModel >> onFairyAnnouncement: anAnnouncement [
	self announcer announce: anAnnouncement
]

{ #category : #'api - subscriptions' }
BVCAINavigationProjectsSessionsModel >> onFinishedBulkChanges: anAnnouncement [
	performingBulkChanges := false.
	needsUpdate ifFalse: [ ^ self ].

	self selectedSession
		ifNotNil: [ :session | session isObsolete ifTrue: [ self deselectSession ] ].
	self notifyProjectsToShowChanged.
	self notifySessionsToShowChanged.
	needsUpdate := false
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustDeselectSession [
	"Just deselect any currently selected session and notify about the changes/
	Return true if there was a session to deselect"

	<return: #Boolean>
	| aPreviouslySelectedSession |
	selectedSession ifNil: [ ^ false ].
	aPreviouslySelectedSession := selectedSession.
	selectedSession := nil.
	selectedSessions := nil.
	self notifySessionDeselected: aPreviouslySelectedSession.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectProject: aProject [
	"Just select a project a notify about the changes"

	selectedProject = aProject ifTrue: [ ^ self ].

	selectedProject := aProject.
	self notifyProjectSelected: aProject.
	self notifySessionsToShowChanged
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectSession: aSession outOfSessions: aCollectionOfSessions [
	"Just select a session and its corresponding project notify about the changes"

	<return: #Boolean>
	| aProjectToSelect |
	selectedSessions := aCollectionOfSessions.

	aProjectToSelect := selectedSession
			ifNil: [ aSession project ]
			ifNotNil: [ :session | session project ].

	selectedSession = aSession ifTrue: [ ^ false ].

	selectedSession := aSession.
	self notifySessionSelected: aSession.
	^ true
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateSessionsInProject: aProject [
	^ aProject sessions asArray
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> projectAdded: aProjectAdded [
	
	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	self notifyProjectsToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> projectRemoved: aProjectRemoved [

	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	self notifyProjectsToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> projectRenamed: aProjectRenamed [

	performingBulkChanges ifTrue: [^needsUpdate := true].

	self notifyProjectsToShowChanged.
	
	"we should still emit it, because other stuff might listen to it to update the label"
	self announcer announce: (GtCoderNavigationClassRenamed new 
		fairy: fairy;
		project: aProjectRenamed projectRenamed;
		oldName: aProjectRenamed oldName;
		newName: aProjectRenamed newName)
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> projectsToShow [
	<return: #Collection of: #BVCAIProject>

	^ self projectsOrganiser sortedProjects
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectFairy: aFairy [
	aFairy isForProject
		ifTrue: [ (fairy isForProject and: [ aFairy project = fairy project ])
				ifTrue: [ ^ self ].
			self assertFairy: aFairy.
			selectedProject := aFairy project.
			self fairy: aFairy.
			self deselectSession.
			self notifySessionsToShowChanged.
			^ self notifyProjectSelected: selectedProject ].

	aFairy isForSession
		ifTrue: [ ^ self selectSession: aFairy theSession withFairy: [ aFairy ] ].

	self assertFairy: aFairy.
	self fairy: aFairy.
	self notifyFairySelected
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectProject: aProject [
	| aFairy |

	(self showProject: aProject)
		ifFalse: [ ^ self ].

	(fairy isForProject and: [ selectedProject = aProject ])
		ifTrue: [ ^ self ].

	selectedProject := aProject.
	aFairy :=  GtPharoPackageCoder forProject: aProject .
	self fairy: aFairy.

	self deselectSession.
	self notifySessionsToShowChanged.

	self notifyProjectSelected: aProject
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSession: aSession [
	self
		selectSession: aSession
		withFairy: [ GtPharoBehaviorCoder forSession: aSession ]
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSession: aSession withFairy: aBlockThatCreatesFairy [
	"Do nothing if a session is already selected"

	self selectSessions: {aSession} withFairy: aBlockThatCreatesFairy
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSessions: aCollectionOfSessions [
	self
		selectSessions: aCollectionOfSessions
		withFairy: [ GtPharoBehaviorCoder forSession: aCollectionOfSessions first ]
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSessions: aCollectionOfSessions withFairy: aBlockThatCreatesFairy [
	"Do nothing if a a session is already selected"

	| aSession |
	aSession := (aCollectionOfSessions includes: selectedSession)
			ifTrue: [ selectedSession ]
			ifFalse: [ aCollectionOfSessions first ].
	selectedSessions := aCollectionOfSessions.

	(selectedSession = aSession
		and: [ fairy isForSession and: [ fairy theSession = aSession ] ])
		ifTrue: [ ^ self ].
		
		"we should set a new fairy as soon as possible, this is because selection and notification methods rely on a specific fairy class. but we shouldn't notify that the fairy has changed just yet"
	self setFairy: (aBlockThatCreatesFairy cull: aSession).
	(self privateJustSelectSession: aSession outOfSessions: aCollectionOfSessions)
		ifTrue: [  "Do any cleanup or preparation" ].
		
		"we should notify that the fairy changed after we select projects, otherwise parts of the fairy that update when fairy is changed will not have access to selected session / project"
	self notifyCoderChanged
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedProject [
	<return: #BVCAUProject>
	^ selectedProject
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedProjectDo: aBlock [
	self selectedProject ifNotNil: aBlock
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedSession [
	<return: #BVCAISession>
	^ selectedSession
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedSessionDo: aBlock [
	self selectedSession ifNotNil: aBlock
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> selectedSessionIsAffectedBy: aSystemAnnouncement [
	"Hook if we ever need to do something basded on system announcements"

	^ false
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedSessions [
	<return: #Collection of: #BVCAISession>
	^ selectedSessions ifNil: [ #() ]
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> sessionAdded: aSessionAdded [
	| aSelectedProject |
	
	aSelectedProject := self selectedProject.
	
	aSelectedProject
		ifNil: [ ^ self ]
		ifNotNil: [ :aProject |
			(aProject includesSessionsAffectedBy: aSessionAdded)
				ifFalse: [ ^ self ] ].
	
	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	self notifySessionsToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> sessionRemoved: aSessionRemoved [
	| aSelectedProject |
	
	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	aSelectedProject := self selectedProject.
	
	aSelectedProject
		ifNil: [ ^ self ]
		ifNotNil: [ :aProject |
			(aProject includesSessionsAffectedBy: aSessionRemoved)
				ifFalse: [ ^ self ] ].

	aSessionRemoved sessionRemoved = self selectedSession
		ifTrue: [ self deselectSession ].

	self notifySessionsToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> sessionRenamed: aSessionRenamed [
	| aSelectedProject |
	
	aSelectedProject := self selectedProject.
	
	aSelectedProject
		ifNil: [ ^ self ]
		ifNotNil: [ :aPackage |
			(aPackage includesClassesAffectedBy: aSessionRenamed)
				ifFalse: [ ^ self ] ].

	performingBulkChanges ifTrue: [^needsUpdate := true].

	self notifySessionsToShowChanged.
	
	"we should still emit it, because other stuff might listen to it to update the label"
	self announcer announce: (GtCoderNavigationClassRenamed new 
		coder: coder;
		project: aSessionRenamed projectAffected;
		theSession: aSessionRenamed sessionRenamed;
		oldName: aSessionRenamed oldName;
		newName: aSessionRenamed newName)
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> sessionsToShow [
	<return: #Collection of: #BVCAISession>

	self hasSelectedProject
		ifFalse: [ ^ #() ].

	^ self privateSessionsInProject: self selectedProject 
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> setFairy: aFairy [
	fairy == aFairy ifTrue: [ ^ false ].
	fairy ifNotNil: [ :oldFairy | oldFairy announcer unsubscribe: self ].

	fairy := aFairy.	"forward coder announcements"
	aFairy announcer weak
		when: Announcement
		send: #onCoderAnnouncement:
		to: self.

	^ true
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> showProject: aProject [
	^ true
]

{ #category : #'api - subscriptions' }
BVCAINavigationProjectsSessionsModel >> subscribeToSystem [
	"Allow subscription to system announcements. Kept from Coder since it's a great idea even though I don't think this will need any system announcements.
	
	SystemAnnouncer uniqueInstance weak
		when: RPackageRegistered send: #packageRegistered: to: self;
		when: RPackageUnregistered send: #packageUnregistered: to: self;
		when: RPackageRenamed send: #packageRenamed: to: self;
		when: ClassTagRenamed send: #packageTagRenamed: to: self;
		when: ClassTagAdded send: #packageTagAdded: to: self"
]

{ #category : #'api - subscriptions' }
BVCAINavigationProjectsSessionsModel >> unsubscribeFromSystem [
	SystemAnnouncer uniqueInstance unsubscribe: self
]
