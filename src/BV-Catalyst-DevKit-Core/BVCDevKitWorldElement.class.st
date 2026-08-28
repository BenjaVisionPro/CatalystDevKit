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

{ #category : #'toolbar actions' }
BVCDevKitWorldElement >> gtWorldThemeActionFor: anAction [
	<gtWorldAction>

	^ anAction explicit
		priority: 45;
		stencil: [ self newThemeButton ]
]

{ #category : #'private - instance creation' }
BVCDevKitWorldElement >> newThemeButton [
	| aThemeDropdown |

	aThemeDropdown := BrButton new
		aptitude: BrGlamorousButtonWithIconAptitude - BrGlamorousButtonExteriorAptitude
			+ (BrGlamorousWithExplicitDropdownAptitude new
				withGainFocusOnShow;
				handle: [ BrButton new
					aptitude: BrGlamorousButtonWithIconAptitude
						- BrGlamorousButtonWithLabelTooltipAptitude2
						- BrGlamorousButtonExteriorAptitude;
					icon: ([ (FontAwesomeIcons icon: #anglesUpDown) size: 16 @ 16 ] asStencil);
					label: 'Theme';
					yourself ];
				content: [ CFThemeChooser new asElement ]);
		icon: ([ (FontAwesomeIcons icon: #anglesUpDown) size: 16 @ 16 ] asStencil);
		label: 'Theme';
		yourself.

	^ aThemeDropdown
]
