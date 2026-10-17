"
Barry, the Catalyst Fairy, in the standard GT chat registry. Refreshes context and editable instructions for each user message.
"
Class {
	#name : 'BVCFairyChat',
	#superclass : 'GtLChat',
	#instVars : [
		'devKitContext'
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

{ #category : 'accessing' }
BVCFairyChat >> devKitContext [
	^ devKitContext
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

{ #category : 'instructions' }
BVCFairyChat >> refreshInstructions [
	"Create a new snapshot so a running child keeps its own instructions."
	self instructions: GtLInstructionComposite new.
	devKitContext configureChat: self forRole: 'Barry'
]

{ #category : 'communication' }
BVCFairyChat >> sendMessage: aMessage [
	self refreshInstructions.
	^ super sendMessage: aMessage
]
