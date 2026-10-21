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

{ #category : 'initialization' }
BVCFairyReplyMessageElement >> initializeToolsExpanderElement [
	"Reuse the GT expander and async sink; only its Barry-local row factory differs."
	toolsHeaderElement := BrLabel new
		aptitude: BrGlamorousLabelAptitude;
		text: 'Activity'.
	toolsContentsElement := BVCFairyUsedToolsElement new
		hMatchParent;
		padding: (BlInsets bottom: 10);
		vFitContentLimited;
		addAptitude: (toolsResizerAptitude := BrGlamorousWithVerticalResizerAptitude new
			beBottom;
			resizerDo: [ :resizer |
				resizer when: BlDoubleClickEvent do: [ :event | self onResizerDoubleClickEvent: event ] ];
			whenResizedDo: [ :event | self onToolsExpanderResized: event ]).
	toolsExpanderElement := BrExpander new
		addAptitude: (BrGlamorousExpanderSubtleAptitude new sidebarExtraPadding: (BlInsets top: 5));
		header: [ toolsHeaderElement ];
		content: [ toolsContentsElement ];
		hMatchParent;
		vFitContentLimited;
		collapse;
		visibility: BlVisibility gone;
		whenExpandedDo: [ :event | self onToolsExpanded: event ];
		whenCollapsedDo: [ :event | self onToolsCollapsed: event ].
	toolsHeaderElement when: BlClickEvent do: [ :event |
		event consumed: true.
		toolsExpanderElement expand ].
	self withAsyncSinkDo: [ :elementSink |
		elementSink
			sink: ((toolsCounter := AsyncCounterSink new) fanout: (toolsPeek := AsyncPeekSink new));
			whenUpdate: [ :element :counterSink | self onToolsCounterSinkUpdate: counterSink ] ]
]

{ #category : 'updating' }
BVCFairyReplyMessageElement >> onToolsCounterSinkUpdate: aFanoutSink [
	| wasHidden |
	wasHidden := toolsExpanderElement visibility = BlVisibility gone.
	super onToolsCounterSinkUpdate: aFanoutSink.
	toolsHeaderElement text: 'Activity — ', toolsCounter count asString, ' observed tool calls (expand)'.
	"Reveal initial activity without overriding a subsequent developer collapse."
	(wasHidden and: [ toolsCounter count > 0 ]) ifTrue: [ toolsExpanderElement expand ]
]
