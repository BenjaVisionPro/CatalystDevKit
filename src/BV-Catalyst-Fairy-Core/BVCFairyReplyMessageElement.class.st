"
Barry document response using the existing GT reply renderer, tools and execution state.
"
Class {
	#name : 'BVCFairyReplyMessageElement',
	#superclass : 'GtLReplyMessageContentElement',
	#category : 'BV-Catalyst-Fairy-Core-UI',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'UI'
}

{ #category : 'initialization' }
BVCFairyReplyMessageElement >> initializeHeaderElement [
	super initializeHeaderElement.
	headerElement addChildFirst: (BVCFairyChat fairyIcon id: #catalystResponseFairy)
]

{ #category : 'initialization' }
BVCFairyReplyMessageElement >> initializeStyling [
	"Document, not a bubble. Retain the existing toolbar and tool resizer behavior."
	self padding: (BlInsets all: 5).
	self background: Color transparent.
	self addAptitude: (BrLazyStyleCommonAptitude new
		when: GtLElementMessageUnfinishedExecutionState uniqueInstance | BlElementState hovered | BlElementState focused
		style: [ :style :theme |
			style do: [ :widget |
				headerElement showToolbarElement.
				mayBeToolsResizerVisible
					ifTrue: [ toolsResizerAptitude showResizer ]
					ifFalse: [ toolsResizerAptitude hideResizer ] ]
			after: [ :widget |
				headerElement hideToolbarElement.
				toolsResizerAptitude hideResizer ] ])
]
