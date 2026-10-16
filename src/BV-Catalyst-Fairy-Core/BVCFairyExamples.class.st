"Executable examples for the Catalyst chat integration and delegation boundaries."
Class {
	#name : #BVCFairyExamples,
	#superclass : #Object,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #examples }
BVCFairyExamples >> parentChat [
	<gtExample>
	| chat |
	chat := BVCFairyChat new provider: BVCFairyProviderStub new.
	self assert: chat devKitContext knowledgeBase uuid asString36 equals: '731asfxqhyhdr96k6wo9yxnzv'.
	self assert: (chat tools anySatisfy: [ :tool | tool name = 'startAgent' ]).
	self assert: (chat tools items noneSatisfy: [ :tool | tool isKindOf: GtLMagritteToolForSmalltalkCodeEvaluation ]).
	^ chat
]

{ #category : #examples }
BVCFairyExamples >> explorerRequest [
	<gtExample>
	^ GtLStartAgentRequest new
		agentName: 'System Explorer';
		taskDescription: 'Inspect the chat boundary';
		prompt: 'Find the Catalyst Chat registration method and report its selector.';
		yourself
]

{ #category : #examples }
BVCFairyExamples >> freshExplorer [
	<gtExample>
	| parent builder child |
	parent := self parentChat.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: self explorerRequest.
	self assert: (builder validateForParent: parent ifErrorDo: [ :problem | self error: problem description ]) isNil.
	child := builder createAgentForParent: parent.
	self assert: child messages isEmpty.
	self assert: child provider ~~ parent provider.
	self assert: child provider modelName equals: parent provider modelName.
	self assert: (child tools items noneSatisfy: [ :tool | tool isKindOf: GtLToolForStartAgent ]).
	self assert: (child tools items noneSatisfy: [ :tool | tool isKindOf: GtLMagritteToolForMethodsCompilation ]).
	self assert: (child tools items noneSatisfy: [ :tool | tool isKindOf: GtLMagritteToolForSmalltalkCodeEvaluation ]).
	self assert: (child instructions instructionString includesSubstring: 'Catalyst System Explorer').
	^ child
]

{ #category : #examples }
BVCFairyExamples >> maintainerTools [
	<gtExample>
	| request child |
	request := self explorerRequest agentName: 'System Maintainer'.
	child := (BVCFairyAgentBuilder forAgentCreationRequest: request)
		createAgentForParent: self parentChat.
	self assert: (child tools anySatisfy: [ :tool | tool isKindOf: GtLMagritteToolForMethodsCompilation ]).
	self assert: (child tools anySatisfy: [ :tool | tool isKindOf: GtLToolForTestClassesRun ]).
	self assert: (child tools items noneSatisfy: [ :tool | tool isKindOf: GtLToolForStartAgent ]).
	^ child
]

{ #category : #examples }
BVCFairyExamples >> narrowedTools [
	<gtExample>
	| parent request child name |
	parent := self parentChat.
	name := GtLMagritteToolForClassLookup new name.
	request := self explorerRequest toolNames: { name }.
	child := (BVCFairyAgentBuilder forAgentCreationRequest: request)
		createAgentForParent: parent.
	self assert: child tools size equals: 1.
	self assert: child tools anyOne name equals: name.
	^ child
]

{ #category : #examples }
BVCFairyExamples >> invalidRole [
	<gtExample>
	| builder problem |
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (self explorerRequest agentName: 'Unbounded assistant').
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | error ].
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> invalidTools [
	<gtExample>
	| builder problem |
	builder := BVCFairyAgentBuilder forAgentCreationRequest:
		(self explorerRequest toolNames: { GtLMagritteToolForMethodsCompilation new name }).
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | error ].
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> invalidPageReference [
	<gtExample>
	| request builder problem callbackWasCalled |
	callbackWasCalled := false.
	request := self explorerRequest instructionPageReferences: {
		GtLLepiterPageReference new databaseId: 'missing'; pageId: 'missing'; yourself }.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: request.
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | callbackWasCalled := true. error ].
	self assert: callbackWasCalled.
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> invalidModel [
	<gtExample>
	| builder problem |
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (self explorerRequest modelName: 'Another model').
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | error ].
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> historyForkIsRejected [
	<gtExample>
	| builder problem |
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (self explorerRequest shouldForkCurrentAgent: true).
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | error ].
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> emptyTaskIsRejected [
	<gtExample>
	| builder problem |
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (self explorerRequest prompt: '  ').
	problem := builder validateForParent: self parentChat ifErrorDo: [ :error | error ].
	self assert: (problem isKindOf: GtLMissingDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> completedTask [
	<gtExample>
	| parent execution result |
	parent := self parentChat.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: self explorerRequest)
		startFromParentAgent: parent
		inContext: (GtLToolExecutionContext new currentChat: parent; objectStorage: parent objectStorage).
	self assert: execution waitUntilCompletionOrTimeout isNil.
	result := execution createAgentResponse.
	self assert: (result isKindOf: GtLAgentExecutionResult).
	self assert: result content content equals: 'Task complete.'.
	self assert: execution executionId isNotNil.
	self assert: (parent announcer hasSubscriber: execution) not.
	^ execution
]

{ #category : #examples }
BVCFairyExamples >> parentCancellation [
	<gtExample>
	| parent execution problem |
	parent := self parentChat.
	parent provider shouldComplete: false.
	parent provider privateExecutionState: GtLProviderState running.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: self explorerRequest)
		startFromParentAgent: parent
		inContext: (GtLToolExecutionContext new currentChat: parent).
	parent stopOngoingExecution.
	problem := execution waitUntilCompletionOrTimeoutAfter: 0.
	self assert: execution isCancelled.
	self assert: execution agent state equals: GtLProviderState stopping.
	self assert: (problem description includesSubstring: 'cancelled').
	self assert: (parent announcer hasSubscriber: execution) not.
	^ execution
]

{ #category : #examples }
BVCFairyExamples >> timeoutStopsChild [
	<gtExample>
	| parent execution problem |
	parent := self parentChat.
	parent provider shouldComplete: false.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: self explorerRequest)
		startFromParentAgent: parent
		inContext: (GtLToolExecutionContext new currentChat: parent).
	problem := execution waitUntilCompletionOrTimeoutAfter: 0.
	self assert: execution agent state equals: GtLProviderState stopping.
	self assert: (problem description includesSubstring: 'timed out').
	self assert: (parent announcer hasSubscriber: execution) not.
	^ execution
]

{ #category : #examples }
BVCFairyExamples >> missingResponse [
	<gtExample>
	| execution problem |
	execution := BVCFairyAgentExecution new agent: (GtLChat new provider: BVCFairyProviderStub new).
	problem := execution createAgentResponse.
	self assert: (problem isKindOf: GtLProblemDomainObject).
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> missingMarkdown [
	<gtExample>
	| child problem |
	child := GtLChat new provider: BVCFairyProviderStub new.
	child addAssistantMessage: (BVCFairyResponseStub new responseModels: Dictionary new).
	problem := (BVCFairyAgentExecution new agent: child) createAgentResponse.
	self assert: (problem description includesSubstring: 'Markdown').
	^ problem
]

{ #category : #examples }
BVCFairyExamples >> instructionEditsAreRefreshed [
	<gtExample>
	| chat snippet original snapshot |
	chat := self parentChat.
	snapshot := chat instructions instructionString.
	snippet := chat devKitContext instructionPages second children first.
	original := snippet string.
	[ snippet string: original, ' Instruction refresh example marker.'.
	  chat sendMarkdown: 'Check the current context.'.
	  self assert: (chat instructions instructionString includesSubstring: 'Instruction refresh example marker.').
	  self assert: (snapshot includesSubstring: 'Instruction refresh example marker.') not ]
		ensure: [ snippet string: original ].
	^ chat
]

{ #category : #examples }
BVCFairyExamples >> chatFromRegistry [
	<gtExample>
	| registry description provider chat |
	registry := GtLChatRegistry new.
	description := registry descriptions detect: [ :each | each label = 'Catalyst Chat' ].
	provider := BVCFairyProviderStub new.
	chat := description newChatWithProvider: provider.
	self assert: chat class equals: BVCFairyChat.
	self assert: chat provider == provider.
	self assert: registry chats size equals: 1.
	self assert: registry chats first == chat.
	^ chat
]

{ #category : #examples }
BVCFairyExamples >> chatElement [
	<gtExample>
	| chat scripter |
	chat := self parentChat.
	scripter := BlScripter new model: chat; element: chat asElement.
	scripter assert exists; // #catalystFairyIcon; play.
	scripter assert exists; // #catalystInstructions; play.
	^ scripter
]

{ #category : #examples }
BVCFairyExamples >> toolCallWithOptionalFieldsOmitted [
	<gtExample>
	| parent call result |
	parent := self parentChat.
	call := GtLFunctionToolCall new
		name: 'startAgent';
		rawArguments: '{"startAgentRequest":{"agentName":"System Explorer","prompt":"Find the chat registration.","taskDescription":"Inspect source"}}';
		yourself.
	result := BVCFairyAgentTool new performToolCall: call
		inContext: (GtLToolExecutionContext new currentChat: parent; objectStorage: parent objectStorage).
	self assert: (result model isKindOf: GtLAgentExecutionResult).
	self assert: result model content content equals: 'Task complete.'.
	^ call
]

{ #category : #examples }
BVCFairyExamples >> popupCreatesCatalystChat [
	<gtExample>
	| registry viewModel element scripter connection |
	registry := GtLChatRegistry new.
	viewModel := registry asViewModel.
	connection := GtLConnection new label: 'Local example'; providerClass: BVCFairyProviderStub.
	viewModel selectedConnection: connection source: self.
	viewModel selectedDescription: (registry descriptions detect: [ :each | each label = 'GT Chat' ]) source: self.
	element := GtLChatRegistryAddNewChatElement new registryViewModel: viewModel.
	scripter := BlScripter new model: registry; element: element.
	scripter click onBrButtonName: 'GT Chat'; play.
	scripter assert exists; onSpaceRoot; // #'menu--label'; @ [ :label | label text asString = 'Catalyst Chat' ]; play.
	scripter click onSpaceRoot; // #'menu--label'; @ [ :label | label text asString = 'Catalyst Chat' ]; play.
	scripter assert exists; onBrButtonName: 'Catalyst Chat'; play.
	scripter click onBrButtonName: 'Add chat'; play.
	self assert: registry chats size equals: 1.
	self assert: registry chats first class equals: BVCFairyChat.
	self assert: registry chats first provider class equals: BVCFairyProviderStub.
	^ scripter
]

{ #category : #examples }
BVCFairyExamples >> instructionsButtonOpensPage [
	<gtExample>
	| scripter openedPage |
	scripter := self chatElement.
	scripter element when: GtPhlowObjectToSpawn do: [ :event | openedPage := event object ].
	scripter click // #catalystInstructions; play.
	self assert: openedPage == scripter model devKitContext instructionPages second.
	^ scripter
]
