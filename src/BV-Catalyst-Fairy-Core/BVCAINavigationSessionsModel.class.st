Class {
	#name : #BVCAINavigationSessionsModel,
	#superclass : #BVCAINavigationModel,
	#traits : 'TGtAnnouncer',
	#classTraits : 'TGtAnnouncer classTrait',
	#instVars : [
		'announcer',
		'coder',
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
BVCAINavigationSessionsModel >> announcer [
	^ announcer ifNil: [ announcer := Announcer new ]
]

{ #category : #asserting }
BVCAINavigationSessionsModel >> assertCoder: aCoder [
	self 
		assert: [ aCoder isNotNil ]
		description: [ 'Coder must be non-nil' ].
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> classAdded: aClassAdded [
	| aSelectedPackage |
	
	aSelectedPackage := self selectedPackage
		ifNil: [ self selectedTag ifNotNil: [ :aTag | aTag package ] ].
	
	aSelectedPackage
		ifNil: [ ^ self ]
		ifNotNil: [ :aPackage |
			(aPackage includesClassesAffectedBy: aClassAdded)
				ifFalse: [ ^ self ] ].

	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	self notifyClassesToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> classModificationApplied: aClassModificationApplied [
	| aSelectedPackage |
	
	aSelectedPackage := self selectedPackage
		ifNil: [ self selectedTag ifNotNil: [ :aTag | aTag package ] ].
	
	aSelectedPackage
		ifNil: [ ^ self ]
		ifNotNil: [ :aPackage |
			(aPackage includesClassesAffectedBy: aClassModificationApplied)
				ifFalse: [ ^ self ] ].

	performingBulkChanges ifTrue: [^needsUpdate := true].

	self notifyClassesToShowChanged.
	self notifySlotsToShowChanged.

	self announcer announce: (GtCoderNavigationClassModified new 
		coder: coder;
		package: aClassModificationApplied packageAffected;
		tag: (self 
			forPharo12AndNewer: [aClassModificationApplied packageTagAffected name] 
			forPharo11:  [ aClassModificationApplied classTagAffected]);
		theClass: aClassModificationApplied classAffected)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> classRemoved: aClassRemoved [
	| aSelectedPackage |

	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	aSelectedPackage := self selectedPackage
		ifNil: [ self selectedTag ifNotNil: [ :aTag | aTag package ] ].
	
	aSelectedPackage
		ifNil: [ ^ self ]
		ifNotNil: [ :aPackage |
			(aPackage includesClassesAffectedBy: aClassRemoved)
				ifFalse: [ ^ self ] ].

	aClassRemoved classRemoved = self selectedClass
		ifTrue: [ self deselectClass ].

	self notifyClassesToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> classRenamed: aClassRenamed [
	| aSelectedPackage |
	
	aSelectedPackage := self selectedPackage
		ifNil: [ self selectedTag ifNotNil: [ :aTag | aTag package ] ].
	
	aSelectedPackage
		ifNil: [ ^ self ]
		ifNotNil: [ :aPackage |
			(aPackage includesClassesAffectedBy: aClassRenamed)
				ifFalse: [ ^ self ] ].

	performingBulkChanges ifTrue: [^needsUpdate := true].

	self notifyClassesToShowChanged.
	
	"we should still emit it, because GtCoderElement listens to it to update the label"
	self announcer announce: (GtCoderNavigationClassRenamed new 
		coder: coder;
		package: aClassRenamed packageAffected;
		tag: (self 
			forPharo12AndNewer: [aClassRenamed packageTagAffected name] 
			forPharo11:  [ aClassRenamed classTagAffected]);
		theClass: aClassRenamed classRenamed;
		oldName: aClassRenamed oldName;
		newName: aClassRenamed newName)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> classReorganized: aClassReorganized [
	self selectedClass = aClassReorganized classReorganized instanceSide
		ifFalse: [ ^ self ].

	performingBulkChanges ifTrue: [^needsUpdate := true].

	self notifyProtocolsToShowChanged
]

{ #category : #'api - subscriptions' }
BVCAINavigationSessionsModel >> classRepackaged: aClassRepackaged [
	(self selectedPackage = aClassRepackaged oldPackage 
		or: [ self selectedPackage = aClassRepackaged newPackage ]) 
			ifFalse: [ ^ self ].

	performingBulkChanges ifTrue: [^needsUpdate := true].
	
	self selectedClass = aClassRepackaged classAffected
		ifTrue: [ self privateJustSelectPackage: aClassRepackaged newPackage ]
		ifFalse: [ self notifyClassesToShowChanged ]
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> classesToShow [
	<return: #Collection of: #Class>

	self hasSelectedPackage
		ifFalse: [ ^ #() ].

	^ self hasSelectedTag
		ifTrue: [ self privateClassesInPackageTag: self selectedTag ]
		ifFalse: [ self privateClassesInPackage: self selectedPackage ]
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> coder: aCoder [
	(self setCoder: aCoder)
		ifFalse: [ ^ self ].

	self notifyCoderChanged
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> coderDo: aBlock [
	coder ifNotNil: aBlock
]

{ #category : #initialization }
BVCAINavigationSessionsModel >> createAllProtocol: aClass [
	^ GtAllProtocol ofClass: aClass
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> deselectClass [
	"Deselect any currently selected class and other entities such as protocols, slots and methods. Deselecting a class means that the model no longer shows any methods, slots or protocols but still continues to display classes".

	(self privateJustDeselectClass)
		ifFalse: [ ^ self ].
	
	self deselectProtocol.
	self notifyProtocolsToShowChanged.
	self deselectSlot.
	self notifySlotsToShowChanged
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> deselectMethod [
	"Deselect any currently selected method and notify about the changes.
	Deselecting a method has no influence on the currently selected protocol, slot or package."

	self privateJustDeselectMethod
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> deselectProtocol [
	"Deselect a currently selected protocol and no longer display methods"
	
	(self privateJustDeselectProtocol)
		ifFalse: [ ^ self ].
	
	self deselectMethod.
	self notifyMethodsToShowChanged
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> deselectSlot [
	"Deselect a currently selected slot and no longer display methods"
	
	(self privateJustDeselectSlot)
		ifFalse: [ ^ self ].
	
	self deselectMethod.
	self notifyMethodsToShowChanged
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasPackageTagsIn: aRPackage [
	<return: #Boolean>
	| hasTags hasExtensions |
	hasTags := (aRPackage tags size = 1
			and: [ aRPackage tags anyOne isRoot ]) not.
	hasExtensions := aRPackage gtDoesExtendClasses.
	^ hasTags or: [ hasExtensions ]
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedClass [
	<return: #Boolean>
	^ self selectedClass isNotNil
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedMethod [
	<return: #Boolean>
	^ self selectedMethod isNotNil
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedPackage [
	<return: #Boolean>
	^ self selectedPackage notNil
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedProtocol [
	<return: #Boolean>
	^ self selectedProtocol isNotNil
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedSlot [
	<return: #Boolean>
	^ self selectedSlot isNotNil
]

{ #category : #'api - testing' }
BVCAINavigationSessionsModel >> hasSelectedTag [
	<return: #Boolean>
	^ self selectedTag notNil
]

{ #category : #initialization }
BVCAINavigationSessionsModel >> initialize [
	super initialize.
	needsUpdate := false.
	performingBulkChanges := false.
	self coder: GtPharoPackagesCoder forAllPackages
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> methodChanged: aMethodAnnouncement [
	self hasSelectedClass ifFalse: [ ^ self ].
	(self selectedClassIsAffectedBy: aMethodAnnouncement) ifFalse: [ ^ self ].

	performingBulkChanges
		ifTrue: [ needsUpdate := true.
			^ self ].

	self notifyProtocolsToShowChanged.
	self notifySlotsToShowChanged.
	self notifyMethodsToShowChanged
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> methodRecategorized: aMethodRecategorized [
	| theClass aPackage aTag |
	self hasSelectedClass ifFalse: [ ^ self ].
	(self selectedClassIsAffectedBy: aMethodRecategorized) ifFalse: [ ^ self ].

	performingBulkChanges
		ifTrue: [ needsUpdate := true.
			^ self ].

	self selectedMethod = aMethodRecategorized methodRecategorized
		ifTrue: [ self deselectMethod ].

	self selectedProtocol
		ifNotNil: [ :aProtocol | 
			(aProtocol name = aMethodRecategorized oldProtocol
				and: [ aProtocol methodSelectors isEmpty ])
				ifTrue: [ (self privateProtocolOfMethod: aMethodRecategorized methodRecategorized)
						ifNotNil: [ :aNewProtocol | self selectProtocol: aNewProtocol ] ] ].

	self notifyProtocolsToShowChanged.
	self notifyMethodsToShowChanged.

	theClass := aMethodRecategorized methodRecategorized methodClass.
	aPackage := theClass package.
	aTag := (GtTagDefinition fromBehavior: theClass) name.

	self announcer
		announce: (GtCoderNavigationClassModified new
				coder: coder;
				package: aPackage;
				tag: aTag;
				theClass: theClass)
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> methodsToShow [
	| anInstanceSideClass aClassSideClass |
	anInstanceSideClass := (self selectedClass ifNil: [ ^ #() ]) instanceSide.
	aClassSideClass := anInstanceSideClass classSide.

	self selectedSlot
		ifNotNil: [ :aSlot | 
			^ Array
				streamContents: [ :aStream | 
					aStream nextPutAll: (anInstanceSideClass methodsAccessingSlot: aSlot).
					aStream nextPutAll: (aClassSideClass methodsAccessingSlot: aSlot) ] ].
	
	^ self selectedProtocol
		ifNil: [ #() ]
		ifNotNil: [ :aProtocol | aProtocol allMethods ]
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyClassDeselected: aPreviouslySelectedClass [
	self announce: (GtCoderNavigationClassDeselected new
		theClass: aPreviouslySelectedClass;
		coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyClassSelected: aClass [
	self
		announce:
			(GtCoderNavigationClassSelected new
				coder: coder;
				package: selectedPackage;
				tag: selectedTag;
				theClass: aClass;
				selectedClasses: self selectedClasses)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyClassSelected: aClass package: anRPackage tag: anRPackageTag [
	self
		announce:
			(GtCoderNavigationClassSelected new
				coder: coder;
				package: anRPackage;
				tag: anRPackageTag;
				theClass: aClass;
				selectedClasses: self selectedClasses)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyClassesToShowChanged [
	self announce: (GtCoderNavigationClassesToShowChanged new coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyCoderChanged [
	self announce: (GtCoderNavigationCoderChanged new coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyCoderSelected [
	self announce: (GtCoderNavigationPackagesSelected new coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyMethodDeselected: aPreviouslySelectedMethod [ 
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyMethodSelected: aMethod [
	coder withSelectedMethod: aMethod.
	self
		announce:
			(GtCoderNavigationMethodSelected new
				coder: coder;
				method: aMethod)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyMethodsSelected: aCollectionOfMethods [
	coder withSelectedMethods: aCollectionOfMethods.
	self
		announce:
			(GtCoderNavigationMethodsSelected new
				coder: coder;
				methods: aCollectionOfMethods)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyMethodsToShowChanged [
	self announce: (GtCoderNavigationMethodsToShowChanged new coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyPackageSelected: anRPackage [
	self
		announce:
			(GtCoderNavigationPackageSelected new
				coder: coder;
				package: anRPackage)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyPackageSelected: anRPackage tag: anRPackageTag [
	self
		announce:
			(GtCoderNavigationPackageTagSelected new
				coder: coder;
				package: anRPackage;
				tag: anRPackageTag)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyProtocolDeselected: aGtPharoProtocol [
	self
		announce:
			(GtCoderNavigationProtocolDeselected new
				coder: coder;
				protocol: aGtPharoProtocol)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyProtocolSelected: aGtPharoProtocol source: aSource [
	self
		announce:
			(GtCoderNavigationProtocolSelected new
				coder: coder;
				protocol: aGtPharoProtocol).

	coder withMethodProtocol: aGtPharoProtocol source: aSource
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifyProtocolsToShowChanged [
	self announce: (GtCoderNavigationProtocolsToShowChanged new coder: coder)
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifySlotDeselected: aPreviouslySelectedProtocol [ 
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifySlotSelected: aSlot source: aSource [
	coder withSlot: aSlot source: aSource
]

{ #category : #'private - notifying' }
BVCAINavigationSessionsModel >> notifySlotsToShowChanged [
	self announce: (GtCoderNavigationSlotsToShowChanged new coder: coder)
]

{ #category : #'api - subscriptions' }
BVCAINavigationSessionsModel >> onAboutToPerformBulkChanges: anAnnouncement [
	performingBulkChanges := true.
	needsUpdate := false
]

{ #category : #'private - announcement handling' }
BVCAINavigationSessionsModel >> onCoderAnnouncement: anAnnouncement [
	self announcer announce: anAnnouncement
]

{ #category : #'api - subscriptions' }
BVCAINavigationSessionsModel >> onFinishedBulkChanges: anAnnouncement [
	performingBulkChanges := false.
	needsUpdate ifFalse: [ ^ self ].

	self selectedClass
		ifNotNil: [ :cls | cls isObsolete ifTrue: [ self deselectClass ] ].
	self notifyClassesToShowChanged.
	self notifySlotsToShowChanged.
	self notifyProtocolsToShowChanged.
	self notifyMethodsToShowChanged.
	needsUpdate := false
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageRegistered: aRPackageRegistered [
	(self packagesToShow includes: aRPackageRegistered package) ifFalse: [ ^ self ].
	
	self announcer announce: (GtCoderNavigationPackageRegistered new 
		coder: coder;
		package: aRPackageRegistered package)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageRenamed: aRPackageRenamed [
	(self packagesToShow includes: aRPackageRenamed package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageRenamed new 
		coder: coder;
		package: aRPackageRenamed package;
		oldName: aRPackageRenamed oldName;
		newName: aRPackageRenamed newName)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageTagAdded: aClassTagAdded [
	(self packagesToShow includes: aClassTagAdded package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageTagAdded new 
		coder: coder;
		package: aClassTagAdded package;
		tag: aClassTagAdded tag)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageTagRemoved: aClassTagRemoved [
	(self packagesToShow includes: aClassTagRemoved package) ifFalse: [ ^ self ].
	self announcer announce: (GtCoderNavigationPackageTagRemoved new 
		coder: coder;
		package: aClassTagRemoved package;
		tag: aClassTagRemoved tag)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageTagRenamed: aClassTagRenamed [
	(self packagesToShow includes: aClassTagRenamed package) ifFalse: [ ^ self ].
	self announcer
		announce: (GtCoderNavigationPackageTagRenamed new
				coder: coder;
				package: aClassTagRenamed package;
				oldName: aClassTagRenamed tag;
				newName: aClassTagRenamed newName)
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> packageUnregistered: aRPackageUnregistered [
	self announcer announce: (GtCoderNavigationPackageUnregistered new 
		coder: coder;
		package: aRPackageUnregistered package)
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> packagesToShow [
	<return: #Collection of: #Package>

	^ self packageOrganizer gtSortedPackages
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> privateAllClassSlotsOf: aBehavior [
	| allSlots |
	
	allSlots := OrderedCollection new.

	aBehavior withAllSuperclassesDo: [ :eachClass |
		eachClass = Object class
			ifTrue: [ ^ allSlots ].
		allSlots addAll: eachClass slots ].
		
	^ allSlots
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> privateAllClassVariablesOf: aBehavior [
	^ Array streamContents: [ :aStream |
		aBehavior withAllSuperclassesDo: [ :eachClass |
			eachClass ~= Object
				ifTrue: [ aStream nextPutAll: eachClass classVariables ] ] ]
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> privateAllSlotsOf: aBehavior [
	| allSlots |
	
	allSlots := OrderedCollection new.

	aBehavior withAllSuperclassesDo: [ :eachClass |
		eachClass = Object
			ifTrue: [ ^ allSlots ].
		allSlots addAll: eachClass slots ].
		
	^ allSlots
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> privateClassesInPackage: aPackage [
	| allClasses |
	allClasses := aPackage definedClasses asSet.
	aPackage extendedClasses do: [ :eachClass |
		allClasses add: eachClass instanceSide ].
	^ allClasses asArray
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> privateClassesInPackageTag: aPackageTag [
	aPackageTag = (GtCoderPackageExtensionTag forPackage: aPackageTag package)
		ifTrue: [
			^ (aPackageTag package extendedClasses
				collect: [ :eachClass | eachClass instanceSide ])
					copyWithoutDuplicates ].

	^ aPackageTag classes
]

{ #category : #'private - selection' }
BVCAINavigationSessionsModel >> privateJustDeselectClass [
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
BVCAINavigationSessionsModel >> privateJustDeselectMethod [
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
BVCAINavigationSessionsModel >> privateJustDeselectProtocol [
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
BVCAINavigationSessionsModel >> privateJustDeselectSlot [
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
BVCAINavigationSessionsModel >> privateJustSelectClass: aClass outOfClasses: aCollectionOfClasses [
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
BVCAINavigationSessionsModel >> privateJustSelectPackage: aPackage [
	"Just select a class a notify about the changes"

	selectedPackage = aPackage
		ifTrue: [ ^ self ].

	selectedPackage := aPackage.
	selectedTag := nil.
	self notifyPackageSelected: aPackage.
	self notifyClassesToShowChanged
]

{ #category : #'private - selection' }
BVCAINavigationSessionsModel >> privateJustSelectPackage: aPackage tag: aTag [
	"Just select a package and a tag a notify about the changes"

	(selectedPackage = aPackage and: [ selectedTag = aTag ])
		ifTrue: [ ^ self ].

	selectedPackage := aPackage.
	selectedTag := aTag.
	self notifyPackageSelected: aPackage tag: aTag.
	self notifyClassesToShowChanged
]

{ #category : #'private - selection' }
BVCAINavigationSessionsModel >> privateJustSelectProtocol: aGtPharoProtocol source: aSourceObject [
	"Just select a protocol a notify about the changes"

	selectedProtocol = aGtPharoProtocol
		ifTrue: [ ^ false ].

	selectedProtocol := aGtPharoProtocol.
	self notifyProtocolSelected: aGtPharoProtocol source: aSourceObject.
	^ true
]

{ #category : #'private - selection' }
BVCAINavigationSessionsModel >> privateJustSelectSlot: aSlot source: aSourceObject [
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
BVCAINavigationSessionsModel >> privateProtocolOfMethod: aCompiledMethod [
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
BVCAINavigationSessionsModel >> privateSelectDefaultProtocolOfClass: aClass [
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
BVCAINavigationSessionsModel >> protocolsToShow [
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
BVCAINavigationSessionsModel >> renameProtocol: aPharoProtocol to: aNewName [
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
BVCAINavigationSessionsModel >> selectClass: aClass [
	self
		selectClass: aClass
		withCoder: [ GtPharoBehaviorCoder forClass: aClass ]
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectClass: aClass withCoder: aBlockThatCreatesCoder [
	"Do nothing if a class is already selected"

	self selectClasses: {aClass} withCoder: aBlockThatCreatesCoder
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectClasses: aCollectionOfClasses [
	self
		selectClasses: aCollectionOfClasses
		withCoder: [ GtPharoBehaviorCoder forClass: aCollectionOfClasses first ]
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectClasses: aCollectionOfClasses withCoder: aBlockThatCreatesCoder [
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
BVCAINavigationSessionsModel >> selectCoder: aCoder [
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
BVCAINavigationSessionsModel >> selectMethod: aMethod [
	self selectClass: aMethod methodClass instanceSide.

	selectedMethod := aMethod.
	self notifyMethodSelected: aMethod
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectMethods: aCollectionOfMethods [
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
BVCAINavigationSessionsModel >> selectPackage: anRPackage [
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
BVCAINavigationSessionsModel >> selectPackageTag: aRPackageTag [
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
BVCAINavigationSessionsModel >> selectProtocol: aPharoProtocol [
	self
		assert: [ aPharoProtocol isNotNil ]
		description: [ 'Protocol must not be nil' ].

	self selectProtocol: aPharoProtocol source: nil
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectProtocol: aPharoProtocol source: aSource [
	self
		privateJustSelectClass: aPharoProtocol protocolClass instanceSide
		outOfClasses: { aPharoProtocol protocolClass instanceSide }.

	(self privateJustSelectProtocol: aPharoProtocol source: aSource)
		ifFalse: [ ^ self ].

	self privateJustDeselectSlot.
	self notifyMethodsToShowChanged
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectSlot: aSlot [
	self
		selectSlot: aSlot
		source: self
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> selectSlot: aSlot source: aSource [
	(self privateJustSelectSlot: aSlot source: aSource)
		ifFalse: [ ^ self ].

	self privateJustDeselectProtocol.
	self deselectMethod.
	self notifyMethodsToShowChanged.
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedClass [
	<return: #Class>
	^ selectedClass
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedClassDo: aBlock [
	self selectedClass ifNotNil: aBlock
]

{ #category : #'event handling' }
BVCAINavigationSessionsModel >> selectedClassIsAffectedBy: aSystemAnnouncement [
	| isClassSideAffected isInstanceSideAffected |
	isInstanceSideAffected := selectedClass instanceSide
			includesMethodsAffectedBy: aSystemAnnouncement.

	isClassSideAffected := selectedClass classSide
			includesMethodsAffectedBy: aSystemAnnouncement.
	^ isInstanceSideAffected or: isClassSideAffected
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedClasses [
	<return: #Collection of: #Class>
	^ selectedClasses ifNil: [ #() ]
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedMethod [
	<return: #CompiledMethod>

	^ selectedMethod
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedMethods [
	<return: #Collection of: #CompiledMethod>

	^ selectedMethods ifNil: [ #() ]
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedPackage [
	<return: #Package>
	^ selectedPackage
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedPackageDo: aBlock [
	self selectedPackage ifNotNil: aBlock
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedProtocol [
	<return: #GtPharoProtocol>

	^ selectedProtocol
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedSlot [
	^ selectedSlot
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedTag [
	<return: #PackageTag>
	^ selectedTag
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> selectedTagDo: aBlock [
	self selectedTag ifNotNil: aBlock
]

{ #category : #'private - accessing' }
BVCAINavigationSessionsModel >> setCoder: aCoder [
	coder == aCoder
		ifTrue: [ ^ false ].
	coder ifNotNil: [ :oldCoder | 
		oldCoder announcer unsubscribe: self ].
	
	coder := aCoder.
	
	"forward coder announcements"
	aCoder announcer weak
		when: Announcement
		send: #onCoderAnnouncement:
		to: self.

	^ true
]

{ #category : #'api - selection' }
BVCAINavigationSessionsModel >> showPackage: anRPackage [
	^ true
]

{ #category : #'api - accessing' }
BVCAINavigationSessionsModel >> slotsToShow [
	<return: #Collection of: #GtPharoProtocol>
	| currentClass instanceSideSlots classSideSlots classVars |

	self hasSelectedClass
		ifFalse: [ ^ #() ].

	currentClass := self selectedClass.

	instanceSideSlots := self privateAllSlotsOf: currentClass instanceSide.
	classSideSlots := self privateAllClassSlotsOf: currentClass classSide.
	classVars := self privateAllClassVariablesOf:currentClass.
	
	^ instanceSideSlots, classSideSlots, classVars
]

{ #category : #'api - subscriptions' }
BVCAINavigationSessionsModel >> subscribeToSystem [
	SystemAnnouncer uniqueInstance weak
		when: RPackageRegistered send: #packageRegistered: to: self;
		when: RPackageUnregistered send: #packageUnregistered: to: self;
		when: RPackageRenamed send: #packageRenamed: to: self;
		when: ClassTagRenamed send: #packageTagRenamed: to: self;
		when: ClassTagAdded send: #packageTagAdded: to: self;
		when: ClassTagRemoved send: #packageTagRemoved: to: self;
		when: ClassAdded send: #classAdded: to: self;
		when: ClassRepackaged send: #classRepackaged: to: self;
		when: ClassRenamed send: #classRenamed: to: self;
		when: ClassRemoved send: #classRemoved: to: self;
		when: ClassModificationApplied send: #classModificationApplied: to: self;
		when: ClassReorganized send: #classReorganized: to: self;
		when: MethodAdded send: #methodChanged: to: self;
		when: MethodRemoved send: #methodChanged: to: self;
		when: MethodRecategorized send: #methodRecategorized: to: self;
		when: GtAboutToPerformBulkChangesAnnouncement
			send: #onAboutToPerformBulkChanges:
			to: self;
		when: GtFinishedBulkChangesAnnouncement
			send: #onFinishedBulkChanges:
			to: self
]

{ #category : #'api - subscriptions' }
BVCAINavigationSessionsModel >> unsubscribeFromSystem [
	SystemAnnouncer uniqueInstance unsubscribe: self
]
