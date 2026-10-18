"
Barry, the Catalyst Fairy, in the standard GT chat registry. Refreshes context and editable instructions for each user message.
"
Class {
	#name : 'BVCFairyChat',
	#superclass : 'GtLChat',
	#instVars : [
		'devKitContext',
		'continuity',
		'continuityRequestId',
		'continuityRunning'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'ui' }
BVCFairyChat class >> fairyIcon [
	^ (Form fromFileNamed: (BVCDevKit iceRepository repositoryDirectory / 'artwork' / 'fairy-icon-transparent.png') fullName)
		asElement asScalableElement size: 32 @ 48
]

{ #category : 'ui' }
BVCFairyChat >> asElement [
	| header |
	header := BrHorizontalPane new
		hMatchParent; vFitContent;
		alignCenterLeft;
		cellSpacing: 8;
		padding: (BlInsets all: 6).
	header addChild: (self class fairyIcon id: #catalystFairyIcon).
	header addChild: (BrLabel new
		aptitude: BrGlamorousLabelAptitude new;
		text: 'Barry, the Catalyst Fairy').
	header addChild: (BrButton new
		id: #catalystInstructions;
		aptitude: BrGlamorousButtonWithLabelAptitude new;
		label: 'Instructions';
		action: [ :button | button phlow spawnObject: devKitContext instructionPages second ]).
	^ BrVerticalPane new
		matchParent;
		addChild: header;
		addChild: super asElement;
		yourself
]

{ #category : 'initialization' }
BVCFairyChat >> buildDefaultProvider [
	| currentProvider |
	currentProvider := super buildDefaultProvider.
	self installCodexClientFor: currentProvider.
	^ currentProvider
]

{ #category : 'continuity' }
BVCFairyChat >> continuity [
	^ continuity ifNil: [ continuity := BVCFairyContinuity default ]
]

{ #category : 'continuity' }
BVCFairyChat >> continuity: aContinuity [
	continuity := aContinuity
]

{ #category : 'continuity' }
BVCFairyChat >> continuityRequestId [
	^ continuityRequestId
]

{ #category : 'accessing' }
BVCFairyChat >> devKitContext [
	^ devKitContext
]

{ #category : 'continuity' }
BVCFairyChat >> finishContinuity: anOutcome [
	| requestId |
	requestId := continuityRequestId.
	requestId ifNil: [ ^ self ].
	[ self continuity recordId: requestId outcome: anOutcome ] ensure: [
		self announcer unsubscribe: self.
		continuityRequestId := nil.
		continuityRunning := false ]
]

{ #category : 'views' }
BVCFairyChat >> gtDevKitContextFor: aView [
	<gtView>
	^ aView columnedList
		title: 'DevKit context';
		priority: 6;
		items: [ devKitContext details ];
		column: 'Name' text: #key;
		column: 'Value' text: #value
]

{ #category : 'printing' }
BVCFairyChat >> gtDisplayOn: aStream [
	aStream nextPutAll: 'Barry, the Catalyst Fairy'.
	self messages ifNotEmpty: [
		aStream nextPutAll: ': '; nextPutAll: self messages first gtDisplayString ]
]

{ #category : 'views' }
BVCFairyChat >> gtInstructionPagesFor: aView [
	<gtView>
	^ aView columnedList
		title: 'Instruction pages';
		priority: 5;
		items: [ devKitContext instructionPages ];
		column: 'Page' text: #title;
		send: #yourself
]

{ #category : 'initialization' }
BVCFairyChat >> initialize [
	super initialize.
	devKitContext := BVCDevKitContext new.
	self
		withDefaultSummarizers;
		markdownResponse;
		tools: BVCDevKitContext readOnlyTools.
	self addTool: BVCFairyAgentTool new.
	self refreshInstructions
]

{ #category : 'initialization' }
BVCFairyChat >> installCodexClientFor: aProvider [
	(aProvider isKindOf: GtLOpenAiCodexProvider) ifFalse: [ ^ self ].
	aProvider model client class = GtLOpenAiCodexClient ifTrue: [
		aProvider model client: (BVCFairyCodexClient preservingClient: aProvider model client) ]
]

{ #category : 'continuity' }
BVCFairyChat >> onContinuityExecutionStateChanged: anAnnouncement [
	continuityRequestId ifNil: [ ^ self ].
	anAnnouncement state = GtLProviderState running ifTrue: [ continuityRunning := true ].
	(anAnnouncement state = GtLProviderState idle and: [ continuityRunning = true ]) ifTrue: [
		self finishContinuity: ((self messages last isReplyMessage and: [ self messages last finalMessage isKindOf: GtLErrorMessage ])
			ifTrue: [ 'provider finished with error; task success unknown; acceptance unverified' ]
			ifFalse: [ 'provider finished; task success unknown; acceptance unverified' ]) ]
]

{ #category : 'accessing' }
BVCFairyChat >> provider: aProvider [
	self installCodexClientFor: aProvider.
	super provider: aProvider
]

{ #category : 'actions' }
BVCFairyChat >> refreshInstructions [
	"Create a new snapshot so a running child keeps its own instructions."
	self instructions: GtLInstructionComposite new.
	devKitContext configureChat: self forRole: 'Barry'.
	self instruction: self continuity contextString titled: 'Barry work continuity'
]

{ #category : 'communication' }
BVCFairyChat >> sendFiles: fileReferences withMessage: aString [
	^ self sendWith: [ :message |
		message markdown: aString.
		fileReferences do: [ :fileReference |
			message addWrappedObject: (GtLFileReference fromFileReference: fileReference) ] ]
]

{ #category : 'actions' }
BVCFairyChat >> sendMessage: aMessage [
	continuityRequestId ifNotNil: [ self error: 'Barry request still active; no overlapping continuity request is supported.' ].
	continuityRequestId := self continuity startKind: 'root' parentId: nil.
	continuityRunning := false.
	self announcer when: GtLChatExecutionStateChanged send: #onContinuityExecutionStateChanged: to: self.
	[ self refreshInstructions.
	  ^ super sendMessage: aMessage ] on: Error do: [ :error |
		self finishContinuity: 'send failed; partial image changes unknown; acceptance unverified'.
		error pass ]
]
