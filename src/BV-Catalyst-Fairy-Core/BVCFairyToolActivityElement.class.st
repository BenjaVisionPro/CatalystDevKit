"
Barry-local actual tool row. Reuses the message view model and its announcements, never the child transcript.
"
Class {
	#name : 'BVCFairyToolActivityElement',
	#superclass : 'GtMessageOneLineMultiLabelSummaryElement',
	#category : 'BV-Catalyst-Fairy-Core-UI',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'UI'
}

{ #category : 'accessing' }
BVCFairyToolActivityElement >> activityText [
	| execution toolMessage |
	execution := self agentExecution.
	execution ifNotNil: [
		^ execution initialRequest agentName, ' — ',
			(execution initialRequest taskDescription asString truncateTo: 160),
			' — ', execution activityLabel ].
	toolMessage := self messageViewModel message.
	(toolMessage isKindOf: GtLToolMessage) ifFalse: [ ^ self messageViewModel contentOneLineSummary asString ].
	^ toolMessage toolName asString, ' — ', toolMessage messageExecutionStateLabel asString,
		' (execution only; not acceptance)'
]

{ #category : 'accessing' }
BVCFairyToolActivityElement >> agentExecution [
	| toolMessage |
	self messageViewModel ifNil: [ ^ nil ].
	toolMessage := self messageViewModel message.
	(toolMessage isKindOf: GtLToolMessage) ifFalse: [ ^ nil ].
	^ toolMessage toolCall catalystAgentExecution
]

{ #category : 'initialization' }
BVCFairyToolActivityElement >> initialize [
	super initialize.
	self addEventHandlerOn: BlElementRemovedFromSceneGraphEvent do: [ :event |
		self messageViewModel ifNotNil: [ self unsubscribeFromMessageViewModel ] ].
	self addEventHandlerOn: BlElementAddedToSceneGraphEvent do: [ :event |
		self messageViewModel ifNotNil: [
			self unsubscribeFromMessageViewModel.
			self subscribeToMessageViewModel.
			self updateElement ] ]
]

{ #category : 'subscriptions' }
BVCFairyToolActivityElement >> subscribeToMessageViewModel [
	super subscribeToMessageViewModel.
	self messageViewModel weak
		when: GtLMessageViewModelExecutionStateChanged
		send: #onMessageViewModelContentsChanged:
		to: self
]

{ #category : 'updating' }
BVCFairyToolActivityElement >> updateElement [
	| execution label |
	self messageViewModel ifNil: [ ^ self ].
	label := BrLabel new
		aptitude: BrGlamorousLabelAptitude;
		text: self activityText;
		hMatchParent.
	self removeChildren; addChild: label.
	execution := self agentExecution.
	execution ifNotNil: [
		self addChild: (BrButton new
			aptitude: BrGlamorousButtonWithLabelAptitude;
			label: 'Child chat';
			action: [ :button | button phlow spawnObject: execution agent ]) ].
	self addChild: (BrButton new
		aptitude: BrGlamorousButtonWithLabelAptitude;
		label: 'Evidence';
		action: [ :button | button phlow spawnObject: self messageViewModel message ])
]
