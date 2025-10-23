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
		'selectedClasses'
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
	self announce: (GtCoderNavigationCoderChanged new fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectDeselected: aPreviouslySelectedProject [
	self
		announce: (GtCoderNavigationClassDeselected new
				project: aPreviouslySelectedProject;
				fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectSelected: aProject [
	self
		announce: (GtCoderNavigationPackageSelected new
				fairy: fairy;
				project: aProject)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifyProjectsToShowChanged [
	self announce: (GtCoderNavigationClassesToShowChanged new fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionDeselected: aPreviouslySelectedSession [
	self
		announce: (GtCoderNavigationClassDeselected new
				theSession: aPreviouslySelectedSession;
				fairy: fairy)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionSelected: aSession [
	self
		announce:
			(GtCoderNavigationClassSelected new
				fairy: fairy;
				project: selectedProject;
				theSession: aSession;
				selectedSessions: self selectedSessions)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionSelected: aSession project: aProject [
	self
		announce: (GtCoderNavigationClassSelected new
				fairy: fairy;
				project: aProject;
				theSession: aSession;
				selectedSessions: self selectedSessions)
]

{ #category : #'private - notifying' }
BVCAINavigationProjectsSessionsModel >> notifySessionsToShowChanged [
	self announce: (GtCoderNavigationClassesToShowChanged new fairy: fairy)
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

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageRegistered: aRPackageRegistered [
	(self packagesToShow includes: aRPackageRegistered package) ifFalse: [ ^ self ].
	
	self announcer announce: (GtCoderNavigationPackageRegistered new 
		coder: coder;
		package: aRPackageRegistered package)
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageRenamed: aRPackageRenamed [
	(self packagesToShow includes: aRPackageRenamed package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageRenamed new 
		coder: coder;
		package: aRPackageRenamed package;
		oldName: aRPackageRenamed oldName;
		newName: aRPackageRenamed newName)
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageTagAdded: aClassTagAdded [
	(self packagesToShow includes: aClassTagAdded package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageTagAdded new 
		coder: coder;
		package: aClassTagAdded package;
		tag: aClassTagAdded tag)
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageTagRemoved: aClassTagRemoved [
	(self packagesToShow includes: aClassTagRemoved package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageTagRemoved new 
		coder: coder;
		package: aClassTagRemoved package;
		tag: aClassTagRemoved tag)
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageTagRenamed: aClassTagRenamed [
	(self packagesToShow includes: aClassTagRenamed package) ifFalse: [ ^ self ].
	self announcer
		announce: (GtCoderNavigationPackageTagRenamed new
				coder: coder;
				package: aClassTagRenamed package;
				oldName: aClassTagRenamed tag;
				newName: aClassTagRenamed newName)
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> packageUnregistered: aRPackageUnregistered [
	self announcer announce: (GtCoderNavigationPackageUnregistered new 
		coder: coder;
		package: aRPackageUnregistered package)
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> packagesToShow [
	<return: #Collection of: #Package>

	^ self packageOrganizer gtSortedPackages
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateAllClassSlotsOf: aBehavior [
	| allSlots |
	
	allSlots := OrderedCollection new.

	aBehavior withAllSuperclassesDo: [ :eachClass |
		eachClass = Object class
			ifTrue: [ ^ allSlots ].
		allSlots addAll: eachClass slots ].
		
	^ allSlots
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateAllClassVariablesOf: aBehavior [
	^ Array streamContents: [ :aStream |
		aBehavior withAllSuperclassesDo: [ :eachClass |
			eachClass ~= Object
				ifTrue: [ aStream nextPutAll: eachClass classVariables ] ] ]
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateAllSlotsOf: aBehavior [
	| allSlots |
	
	allSlots := OrderedCollection new.

	aBehavior withAllSuperclassesDo: [ :eachClass |
		eachClass = Object
			ifTrue: [ ^ allSlots ].
		allSlots addAll: eachClass slots ].
		
	^ allSlots
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateClassesInPackage: aPackage [
	| allClasses |
	allClasses := aPackage definedClasses asSet.
	aPackage extendedClasses do: [ :eachClass |
		allClasses add: eachClass instanceSide ].
	^ allClasses asArray
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateClassesInPackageTag: aPackageTag [
	aPackageTag = (GtCoderPackageExtensionTag forPackage: aPackageTag package)
		ifTrue: [
			^ (aPackageTag package extendedClasses
				collect: [ :eachClass | eachClass instanceSide ])
					copyWithoutDuplicates ].

	^ aPackageTag classes
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustDeselectClass [
	"Just deselect any currently selected class and notify about the changes/
	Return true if there was a class to deselect"
	<return: #Boolean>
	| aPreviouslySelectedClass |

	selectedClass ifNil: [ ^ false ].
	aPreviouslySelectedClass := selectedClass.
	selectedClass := nil.
	selectedClasses := nil.
	self notifyClassDeselected: aPreviouslySelectedClass.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustDeselectMethod [
	"Just deselect any currently selected method and notify about the changes.
	Return true if there was a method to deselect"
	<return: #Boolean>
	| aPreviouslySelectedMethod |

	selectedMethod ifNil: [ ^ false ].
	aPreviouslySelectedMethod := selectedMethod.
	selectedMethod := nil.
	selectedMethods := #().
	self notifyMethodDeselected: aPreviouslySelectedMethod.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustDeselectProtocol [
	"Just deselect any currently selected protocol and notify about the changes.
	Return true if there was a protocol to deselect"
	<return: #Boolean>
	| aPreviouslySelectedProtocol |

	selectedProtocol ifNil: [ ^ false ].
	aPreviouslySelectedProtocol := selectedProtocol.
	selectedProtocol := nil.
	self notifyProtocolDeselected: aPreviouslySelectedProtocol.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustDeselectSlot [
	"Just deselect any currently selected slot and notify about the changes.
	Return true if there was a slot to deselect"
	<return: #Boolean>
	| aPreviouslySelectedSlot |

	selectedSlot ifNil: [ ^ false ].
	aPreviouslySelectedSlot := selectedSlot.
	selectedSlot := nil.
	self notifySlotDeselected: aPreviouslySelectedSlot.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectClass: aClass outOfClasses: aCollectionOfClasses [
	"Just select a class and its corresponding package or tag and notify about the changes"
	| aPackageToSelect aTagToSelect shouldSelectTag |
	<return: #Boolean>
	
	selectedClasses := aCollectionOfClasses.
	
	aPackageToSelect := selectedPackage
		ifNil: [ aClass package ]
		ifNotNil: [ :pkg |
			(pkg extendsClass: aClass)
				ifTrue: [ pkg ]
				ifFalse: [ aClass package ] ].

	"Pre-select a tag under the following conditions:
	 - class comes from a different package than the selected one
	 - there is a selected tag from the same package as a class
	 - class package extends the class"
	shouldSelectTag := aPackageToSelect ~= self selectedPackage.
	shouldSelectTag := shouldSelectTag
		or: [ (aPackageToSelect = self selectedPackage and: [ self hasSelectedTag ]) ].
	
	shouldSelectTag := shouldSelectTag
		and: [ self hasPackageTagsIn: aPackageToSelect ].
	
	shouldSelectTag := shouldSelectTag
		or: [ aPackageToSelect extendsClass: aClass ].


	shouldSelectTag
		ifTrue: [
			aTagToSelect := self 
				forPharo12AndNewer: [ 
					aPackageToSelect tags
		  			detect: [ :tag | tag includesClass: aClass ]
		  			ifNone: [ nil ] ]
				forPharo11: [ 
					aPackageToSelect tagOrNilOf: aClass ].
					
			"pharo issue: the root tag has the same name as the package in Pharo 11
			and Uncategoried in Pharo 12."
			(aTagToSelect isNotNil and: [ aTagToSelect isRoot ])
				ifTrue: [ aTagToSelect := nil ].
			aTagToSelect := aTagToSelect
				ifNil: [
					(aPackageToSelect extendsClass: aClass)
						ifTrue: [ GtCoderPackageExtensionTag forPackage: aPackageToSelect ] ].
		].
	
	aTagToSelect
		ifNil:  [ self privateJustSelectPackage: aPackageToSelect ]
		ifNotNil: [ self privateJustSelectPackage: aPackageToSelect tag: aTagToSelect ].
	
	selectedClass = aClass
		ifTrue: [ ^ false ].

	selectedClass := aClass.
	self notifyClassSelected: aClass.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectPackage: aPackage [
	"Just select a class a notify about the changes"

	selectedPackage = aPackage
		ifTrue: [ ^ self ].

	selectedPackage := aPackage.
	selectedTag := nil.
	self notifyPackageSelected: aPackage.
	self notifyClassesToShowChanged
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectPackage: aPackage tag: aTag [
	"Just select a package and a tag a notify about the changes"

	(selectedPackage = aPackage and: [ selectedTag = aTag ])
		ifTrue: [ ^ self ].

	selectedPackage := aPackage.
	selectedTag := aTag.
	self notifyPackageSelected: aPackage tag: aTag.
	self notifyClassesToShowChanged
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectProtocol: aGtPharoProtocol source: aSourceObject [
	"Just select a protocol a notify about the changes"

	selectedProtocol = aGtPharoProtocol
		ifTrue: [ ^ false ].

	selectedProtocol := aGtPharoProtocol.
	self notifyProtocolSelected: aGtPharoProtocol source: aSourceObject.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateJustSelectSlot: aSlot source: aSourceObject [
	"Just select a slot a notify about the changes"
	self
		assert: [ aSlot isNotNil ]
		description: [ 'Slot must not be nil' ].
		
	selectedSlot = aSlot
		ifTrue: [ ^ false ].

	selectedSlot := aSlot.
	self notifySlotSelected: aSlot source: aSourceObject.
	^ true
]

{ #category : #'private - accessing' }
BVCAINavigationProjectsSessionsModel >> privateProtocolOfMethod: aCompiledMethod [
	| currentProtocol |
	currentProtocol := aCompiledMethod methodClass
		protocolNamed: aCompiledMethod protocol
		ifAbsent: [ nil ].

	^ currentProtocol ifNotNil: [ 
		GtPharoProtocol 
			protocol: currentProtocol 
			class: aCompiledMethod methodClass ]
]

{ #category : #'private - selection' }
BVCAINavigationProjectsSessionsModel >> privateSelectDefaultProtocolOfClass: aClass [
	| aProtocolToSelect thisPackageExtensionProtocol aDefaultProtocol |
	thisPackageExtensionProtocol := self selectedPackage 
		ifNotNil: [ :aPackage | 
			(aClass 
				protocolNamed: '*' , aPackage name
				ifAbsent: [ nil ])
					ifNotNil: [ :aProtocol | 
							GtPharoProtocol 
								protocol: aProtocol 
								class: aClass ] ].

	aDefaultProtocol := thisPackageExtensionProtocol
			ifNil: [ self createAllProtocol: aClass ].

	aProtocolToSelect := selectedProtocol
			ifNil: [ aDefaultProtocol ]
			ifNotNil: [ :aCurrentlySelectedProtocol | 
				self protocolsToShow
					detect: [ :eachProtocol | eachProtocol name = aCurrentlySelectedProtocol name ]
					ifFound: [ :aSimilarProtocol | aSimilarProtocol ]
					ifNone: [ aDefaultProtocol ] ].

	aProtocolToSelect ifNotNil: [ :aProtocol | self selectProtocol: aProtocol ]
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> protocolsToShow [
	<return: #Collection of: #GtPharoProtocol>
	| currentClass classProtocols methodProtocols extension allProtocol |
	self hasSelectedClass ifFalse: [ ^ #() ].

	currentClass := self selectedClass.

	classProtocols := currentClass classSide gtProtocols
			reject: [ :prot |
				prot isEmpty not and: [
					(currentClass classSide methods
						select: [ :meth | (prot includesSelector: meth selector) and: [ meth isFromTrait not ] ])
						isEmpty ] ].
	
	methodProtocols := currentClass gtProtocols.
	extension := false.
	self
		selectedPackageDo: [ :pkg | 
			pkg ~= currentClass package
				ifTrue: [ | protocolName |
					extension := true.
					protocolName := '*' , pkg name.
					methodProtocols := methodProtocols
							select: [ :each | each name beginsWith: protocolName ].
					classProtocols := classProtocols
							select: [ :each | each name beginsWith: protocolName ] ] ].

	methodProtocols := methodProtocols
			collect: [ :eachProtocol | GtPharoProtocol protocol: eachProtocol class: currentClass instanceSide ].

	classProtocols := classProtocols
			collect: [ :eachProtocol | GtPharoProtocol protocol: eachProtocol class: currentClass classSide ].

	allProtocol := self createAllProtocol: currentClass.

	^ { allProtocol } , methodProtocols , classProtocols
]

{ #category : #'api - refactorings' }
BVCAINavigationProjectsSessionsModel >> renameProtocol: aPharoProtocol to: aNewName [
	| refactoring |

	refactoring := GtRBRenameProtocolRefactoring
		renameProtocol: aPharoProtocol name
		in: aPharoProtocol protocolClass
		to: aNewName.
	refactoring execute.

	self selectProtocol: (GtPharoProtocol 
		protocolNamed: aNewName
		class: aPharoProtocol protocolClass)
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectClass: aClass [
	self
		selectClass: aClass
		withCoder: [ GtPharoBehaviorCoder forClass: aClass ]
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectClass: aClass withCoder: aBlockThatCreatesCoder [
	"Do nothing if a class is already selected"

	self selectClasses: {aClass} withCoder: aBlockThatCreatesCoder
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectClasses: aCollectionOfClasses [
	self
		selectClasses: aCollectionOfClasses
		withCoder: [ GtPharoBehaviorCoder forClass: aCollectionOfClasses first ]
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectClasses: aCollectionOfClasses withCoder: aBlockThatCreatesCoder [
	"Do nothing if a class is already selected"

	| aClass |
	aClass := (aCollectionOfClasses includes: selectedClass)
			ifTrue: [ selectedClass ]
			ifFalse: [ aCollectionOfClasses first ].
	selectedClasses := aCollectionOfClasses.

	(selectedClass = aClass
			and: [ coder isForClass 
			and: [ coder theClass = aClass ] ]) 
				ifTrue: [ ^ self ].
	
	"we should set a new coder as soon as possible, this is because selection and notification methods rely on a specific coder class. but we shouldn't notify that the coder has changed just yet"
	self setCoder: (aBlockThatCreatesCoder cull: aClass).
	(self privateJustSelectClass: aClass outOfClasses: aCollectionOfClasses)
		ifTrue: [ self deselectSlot.
			self notifySlotsToShowChanged.
			self notifyProtocolsToShowChanged.
			self privateSelectDefaultProtocolOfClass: aClass ].
			
	"we should notify that the coder changed after we select packages / tags and protocols, otherwise parts of the coder that update when coder is changed will not have access to selected class / package"
	self notifyCoderChanged
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectCoder: aCoder [
	aCoder isForPackage
		ifTrue: [ (coder isForPackage and: [ aCoder package = coder package ])
				ifTrue: [ ^ self ].
			self assertCoder: aCoder.
			selectedPackage := aCoder package.
			selectedTag := nil.
			self coder: aCoder.
			self deselectClass.
			self notifyClassesToShowChanged.
			^ self notifyPackageSelected: selectedPackage ].
	aCoder isForPackageTag
		ifTrue: [ (coder isForPackageTag and: [ aCoder packageTag = coder packageTag ])
				ifTrue: [ ^ self ].
			self assertCoder: aCoder.
			selectedPackage := aCoder package.
			selectedTag := aCoder packageTag.
			self coder: aCoder.
			self deselectClass.
			self notifyClassesToShowChanged.
			^ self notifyPackageSelected: selectedPackage tag: selectedTag ].

	aCoder isForClass
		ifTrue: [ ^ self selectClass: aCoder theClass withCoder: [ aCoder ] ].

	self assertCoder: aCoder.
	self coder: aCoder.
	self notifyCoderSelected
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectMethod: aMethod [
	self selectClass: aMethod methodClass instanceSide.

	selectedMethod := aMethod.
	self notifyMethodSelected: aMethod
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectMethods: aCollectionOfMethods [
	aCollectionOfMethods ifEmpty: [ ^ self ].
	aCollectionOfMethods size = 1 ifTrue: [
		self selectMethod: aCollectionOfMethods anyOne.
		^ self ].

	self selectClass: aCollectionOfMethods anyOne methodClass instanceSide.

	selectedMethod := aCollectionOfMethods anyOne.
	selectedMethods := aCollectionOfMethods.
	self notifyMethodsSelected: aCollectionOfMethods
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectPackage: anRPackage [
	| aCoder |

	(self showPackage: anRPackage)
		ifFalse: [ ^ self ].

	(coder isForPackage and: [ selectedPackage = anRPackage ])
		ifTrue: [ ^ self ].

	selectedPackage := anRPackage.
	selectedTag := nil.
	aCoder := coder isForPackageTag
			ifTrue: [ coder packageCoder ]
			ifFalse: [ GtPharoPackageCoder forPackage: anRPackage ].
	self coder: aCoder.

	self deselectClass.
	self notifyClassesToShowChanged.

	self notifyPackageSelected: anRPackage
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectPackageTag: aRPackageTag [
	| packageCoder aCoder |

	aRPackageTag
		ifNil: [ ^ self ].

	(self showPackage: aRPackageTag package)
		ifFalse: [ ^ self ].

	(coder isForPackageTag
		and: [ selectedPackage = aRPackageTag package and: [ selectedTag = aRPackageTag ] ])
		ifTrue: [ ^ self ].

	packageCoder := ((coder isForPackage
			and: [ selectedPackage = aRPackageTag package ]) ifTrue: [ coder ])
			ifNil: [ selectedPackage := aRPackageTag package.
				GtPharoPackageCoder forPackage: aRPackageTag package ].
	aCoder := packageCoder packageTagCoderFor: aRPackageTag.
	self coder: aCoder.
	
	selectedPackage := aRPackageTag package.
	selectedTag := aRPackageTag.
	
	self deselectClass.
	self notifyClassesToShowChanged.

	self
		notifyPackageSelected: aRPackageTag package
		tag: aRPackageTag
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectProtocol: aPharoProtocol [
	self
		assert: [ aPharoProtocol isNotNil ]
		description: [ 'Protocol must not be nil' ].

	self selectProtocol: aPharoProtocol source: nil
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectProtocol: aPharoProtocol source: aSource [
	self
		privateJustSelectClass: aPharoProtocol protocolClass instanceSide
		outOfClasses: { aPharoProtocol protocolClass instanceSide }.

	(self privateJustSelectProtocol: aPharoProtocol source: aSource)
		ifFalse: [ ^ self ].

	self privateJustDeselectSlot.
	self notifyMethodsToShowChanged
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSlot: aSlot [
	self
		selectSlot: aSlot
		source: self
]

{ #category : #'api - selection' }
BVCAINavigationProjectsSessionsModel >> selectSlot: aSlot source: aSource [
	(self privateJustSelectSlot: aSlot source: aSource)
		ifFalse: [ ^ self ].

	self privateJustDeselectProtocol.
	self deselectMethod.
	self notifyMethodsToShowChanged.
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedClass [
	<return: #Class>
	^ selectedClass
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedClassDo: aBlock [
	self selectedClass ifNotNil: aBlock
]

{ #category : #'event handling' }
BVCAINavigationProjectsSessionsModel >> selectedClassIsAffectedBy: aSystemAnnouncement [
	| isClassSideAffected isInstanceSideAffected |
	isInstanceSideAffected := selectedClass instanceSide
			includesMethodsAffectedBy: aSystemAnnouncement.

	isClassSideAffected := selectedClass classSide
			includesMethodsAffectedBy: aSystemAnnouncement.
	^ isInstanceSideAffected or: isClassSideAffected
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedClasses [
	<return: #Collection of: #Class>
	^ selectedClasses ifNil: [ #() ]
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedMethod [
	<return: #CompiledMethod>

	^ selectedMethod
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedMethods [
	<return: #Collection of: #CompiledMethod>

	^ selectedMethods ifNil: [ #() ]
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedPackage [
	<return: #Package>
	^ selectedPackage
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedPackageDo: aBlock [
	self selectedPackage ifNotNil: aBlock
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedProtocol [
	<return: #GtPharoProtocol>

	^ selectedProtocol
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedSlot [
	^ selectedSlot
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedTag [
	<return: #PackageTag>
	^ selectedTag
]

{ #category : #'api - accessing' }
BVCAINavigationProjectsSessionsModel >> selectedTagDo: aBlock [
	self selectedTag ifNotNil: aBlock
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
