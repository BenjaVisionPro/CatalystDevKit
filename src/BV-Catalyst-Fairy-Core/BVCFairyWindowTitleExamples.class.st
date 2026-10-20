"
Focused offline checks for Barry chat titles through the Catalyst world spawn path. Each example removes its temporary tabs and scene graph.
"
Class {
	#name : 'BVCFairyWindowTitleExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyWindowTitleExamples >> chatWindowTitleAfterMessage [
	<gtExample>
	| chat |
	chat := BVCFairyExamples new chatFromRegistry.
	self withWorldDo: [ :world :scripter |
		| windowSpace |
		world phlow spawnObject: chat.
		windowSpace := world tabs tabs last model.
		chat addMessage: (chat createUserMessage string: 'An offline title regression message').
		scripter pulse.
		self assert: windowSpace title asString equals: 'Barry'.
		world phlow spawnObject: chat.
		self assert: world tabs tabs last model title asString equals: 'Barry' ].
	^ chat
]

{ #category : 'private' }
BVCFairyWindowTitleExamples >> evaluateOnUIProcess: anExampleBlock [
	"Dispatch to the active Winit universe, not the retired default universe."
	^ BVCFairyUIRequest value: anExampleBlock
		on: BlParallelUniverse winit
		withinMilliseconds: 2000
]

{ #category : 'examples' }
BVCFairyWindowTitleExamples >> nativeChatWindowTitle [
	<gtExample>
	| chat windowSpace evidence waitUntil |
	chat := BVCFairyExamples new chatFromRegistry.
	evidence := Dictionary new.
	waitUntil := [ :condition |
		| deadlineMilliseconds |
		deadlineMilliseconds := Time millisecondClockValue + 5000.
		[ (self evaluateOnUIProcess: condition) or: [ Time millisecondClockValue >= deadlineMilliseconds ] ]
			whileFalse: [ (Delay forMilliseconds: 10) wait ].
		self assert: (self evaluateOnUIProcess: condition) ].
	self withWorldDo: [ :world :scripter |
		world phlow spawnObject: chat.
		windowSpace := world tabs tabs last model.
		world closeAllTabs.
		windowSpace root removeFromParent ].
	[
		self evaluateOnUIProcess: [ windowSpace show ].
		waitUntil value: [ windowSpace hasHostSpace ].
		self evaluateOnUIProcess: [
			self assert: windowSpace hostSpace title asString equals: 'Barry'.
			evidence at: #initialTitle put: windowSpace hostSpace title asString.
			chat addMessage: (chat createUserMessage string: 'Offline native window title check').
			self assert: windowSpace hostSpace title asString equals: 'Barry'.
			evidence
				at: #titleAfterMessage put: windowSpace hostSpace title asString;
				at: #hostClass put: windowSpace host class;
				at: #platform put: Smalltalk version;
				at: #chat put: chat ]
	] ensure: [
		self evaluateOnUIProcess: [ windowSpace close ].
		waitUntil value: [ windowSpace isOpened not and: [ windowSpace hasHostSpace not ] ].
		self evaluateOnUIProcess: [ windowSpace root removeChildren ] ].
	evidence at: #windowClosed put: (self evaluateOnUIProcess: [ windowSpace isOpened not ]).
	^ evidence
]

{ #category : 'examples' }
BVCFairyWindowTitleExamples >> newChatWindowTitle [
	<gtExample>
	| chat |
	chat := BVCFairyExamples new chatFromRegistry.
	self withWorldDo: [ :world :scripter |
		| spawnEvent windowSpace |
		spawnEvent := world phlow spawnObject: chat.
		self assert: spawnEvent isConsumed.
		self assert: world tabs tabs size equals: 2.
		windowSpace := world tabs tabs last model.
		self assert: windowSpace title asString equals: 'Barry'.
		self assert: world tabs tabs last tabLabel text asString equals: 'Barry'.
		self assert: windowSpace root children first class equals: GtPagerSettings usedPager ].
	^ chat
]

{ #category : 'examples' }
BVCFairyWindowTitleExamples >> ordinaryChatWindowTitleIsUnchanged [
	<gtExample>
	| chat |
	chat := GtLChat new provider: BVCFairyProviderStub new.
	self withWorldDo: [ :world :scripter |
		| spawnEvent windowSpace |
		spawnEvent := world phlow spawnObject: chat.
		self assert: spawnEvent isConsumed.
		windowSpace := world tabs tabs last model.
		self assert: windowSpace title equals: BlSpace new defaultTitle.
		self assert: chat gtDefaultInspectorTool name equals: 'Chat: Chat' ].
	^ chat
]

{ #category : 'private' }
BVCFairyWindowTitleExamples >> withWorldDo: anExampleBlock [
	^ self evaluateOnUIProcess: [
		| world scripter |
		world := BVCDevKitWorldElement new.
		scripter := BlScripter new element: world.
		[ anExampleBlock value: world value: scripter ]
			ensure: [
				world closeAllTabs.
				world removeFromParent.
				scripter space root removeChildren.
				"BlScripterSpace uses a mocked host and always reports itself open."
				self assert: scripter space hasHostSpace not.
				self assert: scripter space root children isEmpty ] ]
]
