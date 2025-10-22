Class {
	#name : #BVCAIToolbarElement,
	#superclass : #BVCAIAbstractElement,
	#instVars : [
		'toolbarElement'
	],
	#category : #'BV-Catalyst-Fairy-Core-Basic'
}

{ #category : #initialization }
BVCAIToolbarElement >> addCustomButtons [
	| classToUse |
	classToUse := self navigationModel hasSelectedClass
			ifTrue: [ self navigationModel selectedClass ]
			ifFalse: [ self navigationModel hasSelectedPackage
					ifTrue: [ self navigationModel selectedPackage ]
					ifFalse: [ self class ] ].
	(GtPhlowClassActionsCollector new
		pragmaName: #gtClassAction;
		from: classToUse class;
		to: Behavior;
		collect)
		do: [ :each | 
			each
				asElement: [ :actionElement | self toolbarElement addItem: actionElement ]
				withHostElement: self ]
]

{ #category : #initialization }
BVCAIToolbarElement >> initialize [
	super initialize.
	self initializeToolbarElement.
	
	self layout: BlLinearLayout horizontal.

	self addChild: self toolbarElement as: #toolbar.
	
	self addAptitude: (BrLayoutResizerAptitude new
		anyToFitContent;
		anyToFitContent: self toolbarElement)
]

{ #category : #initialization }
BVCAIToolbarElement >> initializeToolbarElement [
	toolbarElement := BrToolbar new
			aptitude: BrGlamorousToolbarAptitude new;
			padding: (BlInsets right: 5).
]

{ #category : #initialization }
BVCAIToolbarElement >> onNavigationModelChanged [
	self updateCustomButtons
]

{ #category : #accessing }
BVCAIToolbarElement >> toolbarElement [
	<return: #BrToolbar>
	^ toolbarElement
]

{ #category : #initialization }
BVCAIToolbarElement >> updateCustomButtons [
	toolbarElement removeChildren.
	self addCustomButtons
]
