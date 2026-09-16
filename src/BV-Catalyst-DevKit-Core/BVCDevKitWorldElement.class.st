Class {
	#name : 'BVCDevKitWorldElement',
	#superclass : 'GtWorldElement',
	#category : 'BV-Catalyst-DevKit-Core',
	#package : 'BV-Catalyst-DevKit-Core'
}

{ #category : 'defaults' }
BVCDevKitWorldElement >> defaultHomeElement [
	^ BVCDevKitHome new
]

{ #category : 'defaults' }
BVCDevKitWorldElement >> defaultHomeTabIcon [
	^ BVCDevKitVectorIcons icon: #bvcServer size: 32 @ 32
]

{ #category : 'world actions' }
BVCDevKitWorldElement >> gtFoundationThemeToggleActionFor: anAction [
	<gtWorldAction>

	^ anAction explicit
		priority: 1;
		stencil: [ CFThemeToggleButton forElement: self ]
]

{ #category : 'world actions' }
BVCDevKitWorldElement >> gtFoundationThemeChooserActionFor: anAction [
	<gtWorldAction>

	^ anAction explicit
		priority: 2;
		stencil: [ CFThemeChooserButton forElement: self ]
]

{ #category : #'private - instance creation' }
BVCDevKitWorldElement >> newSpotterButton [
	| spotterDropdown |

	spotterDropdown := GtSpotterDropdownButtonStencil new
		id: GtWorldSpotterSearchElementId;
		icon: (FontAwesomeIcons icon: #magnifyingGlass);
		tooltip: 'Search';
		valuable: [ GtWorldSpotterSearchStart new
			knowledgeBase: self knowledgeBase ];
		extent: [ self class worldSpotterSize ];
		showPreview: [ self class isWorldSpotterPreviewDisplayed ];
		onPreviewChangedSend: #onShowWorldSpotterPreview: to: self class;
		spotterElementDo: [ :aSpotterElement |
			aSpotterElement
				when: GtSpotterResizedEvent
				do: [ :anEvent |
					self onResizedSpotter: aSpotterElement event: anEvent ] ];
		actOn: [ :anAnnouncement :aRawObject :aButton |
			anAnnouncement beActed.
			aButton phlow spawnTool: anAnnouncement toolToSend ];
		asElement.
	spotterDropdown aptitude - BrGlamorousButtonExteriorAptitude.
	spotterDropdown
		when: GtPhlowObjectToSpawn
		do: [ :anEvent |
			anEvent consumed: true.
			anEvent object gtSpotterActDefaultFrom: self currentSpotterButton ].

	^ spotterDropdown
]

{ #category : #'private - instance creation' }
BVCDevKitWorldElement >> newChatRegistryDropdown [
	^ GtLWorldChatRegistryDropdown new
		initializeForWorldElement: self;
		icon: (FontAwesomeIcons icon: #messageBot);
		yourself
]

{ #category : #'private - instance creation' }
BVCDevKitWorldElement >> newSubSpaceButton [
	| menuIcon newSubSpaceDropdown |

	menuIcon := [ FontAwesomeIcons icon: #bars ].
	newSubSpaceDropdown := BrButton new
		id: GtWorldMenuElementId;
		aptitude: BrGlamorousButtonWithIconAptitude - BrGlamorousButtonExteriorAptitude
			+ (BrGlamorousWithExplicitDropdownAptitude new
				withGainFocusOnShow;
				handle: [ BrButton new
					aptitude: BrGlamorousButtonWithIconAptitude - BrGlamorousButtonWithLabelTooltipAptitude2
						- BrGlamorousButtonExteriorAptitude;
					icon: menuIcon value;
					label: 'Menu';
					yourself ]
					content: [ BrScrollPane new
						aptitude: BrScrollPaneAptitude + BrGlamorousWithVerticalScrollbarAptitude;
						hExact: 420;
						vFitContentLimited;
						content: (GtToolsMenu new
							knowledgeBase: self knowledgeBase;
							yourself) ]);
		icon: menuIcon value;
		label: 'Menu';
		yourself.

	^ newSubSpaceDropdown
]
