Class {
	#name : #BVCAIPlaygroundElement,
	#superclass : #BVCAIAbstractElement,
	#instVars : [
		'contentElement',
		'playgroundElement'
	],
	#category : #'BV-Catalyst-Fairy-Core-Basic'
}

{ #category : #'private - accessing' }
BVCAIPlaygroundElement >> contentElement [
	<return: #GtCoderContentElement>
	^ contentElement
]

{ #category : #accessing }
BVCAIPlaygroundElement >> disablePlayPage [
	self removeChild: self playPageElement
]

{ #category : #initialization }
BVCAIPlaygroundElement >> initialize [
	super initialize.
	
	self initializeContentElement.
	self initializePlayPageElement.
	
	self layout: BlLinearLayout vertical.
	
	self addChild: self contentElement as: #content.
	self addChild: self playPageElement as: #playPage
]

{ #category : #initialization }
BVCAIPlaygroundElement >> initializeContentElement [
	contentElement := GtCoderContentElement new.
]

{ #category : #initialization }
BVCAIPlaygroundElement >> initializePlayPageElement [
	playgroundElement := (GtInspector environment 
		at: GtInspector embeddedPlaygroundName) new.

	playgroundElement collapse.
	playgroundElement objectHolder: self objectHolder
]

{ #category : #'private - accessing' }
BVCAIPlaygroundElement >> objectHolder [
	^ GtInspectorObject new object: self receiver
]

{ #category : #'private - hooks' }
BVCAIPlaygroundElement >> onClassSelected: anEvent [
	self updatePlayground
]

{ #category : #'private - hooks' }
BVCAIPlaygroundElement >> onNavigationModelChanged [
	super onNavigationModelChanged.
	self contentElement navigationModel: self navigationModel.
	self updatePlayground.
]

{ #category : #'private - hooks' }
BVCAIPlaygroundElement >> onPackageSelected: anEvent [
	self inUIProcessDo: [ self updatePlayground ]
]

{ #category : #'private - hooks' }
BVCAIPlaygroundElement >> onPackageTagSelected: anEvent [
	self inUIProcessDo: [ self updatePlayground ]
]

{ #category : #'private - hooks' }
BVCAIPlaygroundElement >> onPackagesSelected: anEvent [
	self inUIProcessDo: [ self updatePlayground ]
]

{ #category : #'private - accessing' }
BVCAIPlaygroundElement >> playPageElement [
	<return: #GtPhlowVerticalSidebarElement>
	^ playgroundElement
]

{ #category : #'private - accessing' }
BVCAIPlaygroundElement >> receiver [
	self navigationModel selectedClassDo: [ :aClass | ^ aClass ].
	self navigationModel selectedTagDo: [ :aPackageTag | ^ aPackageTag ].
	self navigationModel selectedPackageDo: [ :aPackage | ^ aPackage ].
	^ Smalltalk
]

{ #category : #'private - subscriptions' }
BVCAIPlaygroundElement >> subscribeToNavigationModel [
	super subscribeToNavigationModel.
	self navigationModel weak
		when: GtCoderNavigationPackagesSelected send: #onPackagesSelected: to: self;
		when: GtCoderNavigationPackageSelected send: #onPackageSelected: to: self;
		when: GtCoderNavigationPackageTagSelected send: #onPackageTagSelected: to: self;
		when: GtCoderNavigationClassSelected send: #onClassSelected: to: self.
]

{ #category : #'private - updating' }
BVCAIPlaygroundElement >> updatePlayground [
	self playPageElement objectHolder: self objectHolder
]
