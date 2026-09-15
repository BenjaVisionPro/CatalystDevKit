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
		priority: 60;
		stencil: [ CFThemeToggleButton forElement: self ]
]

{ #category : 'world actions' }
BVCDevKitWorldElement >> gtFoundationThemeChooserActionFor: anAction [
	<gtWorldAction>

	^ anAction explicit
		priority: 61;
		stencil: [ CFThemeChooserButton forElement: self ]
]
