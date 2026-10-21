"
Controlled examples for Barry compact actual tool and delegated-child feedback.
"
Class {
	#name : 'BVCFairyActivityExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyActivityExamples >> childChatAction [
	<gtExample>
	| row spawned |
	row := self delayedChildBeforeReturn.
	row addEventHandlerOn: GtPhlowObjectToSpawn do: [ :event |
		spawned := event object.
		event consumed: true ].
	row children second action value: row children second.
	self assert: spawned == row agentExecution agent.
	^ row
]

{ #category : 'examples' }
BVCFairyActivityExamples >> compactActivityPresentation [
	<gtExample>
	| parent child execution toolCall toolMessage row reply viewModel pane |
	parent := BVCFairyExamples new parentChat.
	child := GtLChat new provider: (BVCFairyProviderStub new shouldComplete: false).
	execution := BVCFairyAgentExecution new parentAgent: parent; agent: child;
		initialRequest: BVCFairyExamples new explorerRequest.
	toolCall := GtLFunctionToolCall new name: 'startAgent'; arguments: Dictionary new.
	toolMessage := GtLToolMessage new toolCall: toolCall.
	parent addToolMessage: toolMessage.
	execution bindFeedbackToToolCall: toolCall.
	toolMessage beRunningExecutionState.
	viewModel := parent asViewModel messageViewModels detect: [ :model |
		(model isKindOf: GtLNewMessageViewModel) not and: [ model message isKindOf: GtLReplyMessage ] ].
	reply := BVCFairyReplyMessageElement newForChatList messageViewModel: viewModel.
	row := BVCFairyToolActivityElement new messageViewModel: (GtLToolMessageViewModel new message: toolMessage).
	pane := BrVerticalPane new hExact: 1000; vFitContent; addChild: row; addChild: reply.
	pane forceLayout.
	self assert: row children size equals: 3.
	self assert: (reply instVarNamed: 'toolsContentsElement') class equals: BVCFairyUsedToolsElement.
	self assert: (GtLMessageUsedToolsElement new newListItemElement class) equals: GtMessageOneLineMultiLabelSummaryElement.
	^ pane
]

{ #category : 'examples' }
BVCFairyActivityExamples >> delayedChildBeforeReturn [
	<gtExample>
	| parent child execution toolCall toolMessage row |
	parent := BVCFairyExamples new parentChat.
	child := GtLChat new provider: (BVCFairyProviderStub new shouldComplete: false).
	execution := BVCFairyAgentExecution new
		parentAgent: parent; agent: child;
		initialRequest: BVCFairyExamples new explorerRequest.
	toolCall := GtLFunctionToolCall new name: 'startAgent'.
	toolMessage := GtLToolMessage new toolCall: toolCall.
	parent addToolMessage: toolMessage.
	toolMessage beRunningExecutionState.
	execution registerTerminationSignal.
	[ child sendMarkdown: 'Controlled delayed task'.
	  execution bindFeedbackToToolCall: toolCall.
	  row := BVCFairyToolActivityElement new messageViewModel: (GtLToolMessageViewModel new message: toolMessage).
	  self assert: row agentExecution == execution.
	  self assert: (row activityText includesSubstring: 'System Explorer').
	  self assert: (row activityText includesSubstring: 'Inspect the chat boundary').
	  self assert: (row activityText includesSubstring: 'Running').
	  self assert: row children size equals: 3.
	  self assert: execution responseMessage isNil.
	  self assert: (row children second label asString) equals: 'Child chat'.
	  ^ row
	] ensure: [ execution cancel. execution unsubscribe ]
]

{ #category : 'examples' }
BVCFairyActivityExamples >> delayedToolPublishesBeforeReturn [
	<gtExample>
	| parent toolCall toolMessage finished worker result execution notifications |
	parent := BVCFairyExamples new parentChat.
	parent provider shouldComplete: false.
	toolCall := GtLFunctionToolCall new name: 'startAgent';
		rawArguments: (STONJSON toString: { 'startAgentRequest' -> {
			'agentName' -> 'System Explorer'. 'prompt' -> 'Controlled delayed example.'.
			'taskDescription' -> 'Controlled delayed inspection' } asDictionary } asDictionary).
	toolMessage := GtLToolMessage new toolCall: toolCall.
	parent addToolMessage: toolMessage.
	notifications := Semaphore new.
	toolMessage when: GtLMessageContentsChanged send: #signal to: notifications.
	finished := Semaphore new.
	worker := [ [ result := BVCFairyAgentTool new performToolCall: toolCall
		inContext: (GtLToolExecutionContext new currentChat: parent; objectStorage: parent objectStorage) ]
		ensure: [ finished signal ] ] fork.
	[
		self assert: (notifications waitTimeoutSeconds: 2) not.
		execution := toolCall catalystAgentExecution.
		self assert: execution notNil.
		self assert: result isNil.
		self assert: worker isTerminated not.
		self assert: execution agent state equals: GtLProviderState running.
		execution cancel.
		self assert: (finished waitTimeoutSeconds: 2) not.
		self assert: result model agentExecution == execution.
		^ execution
	] ensure: [
		execution ifNotNil: [ execution cancel. execution unsubscribe ].
		toolMessage unsubscribe: notifications ]
]

{ #category : 'examples' }
BVCFairyActivityExamples >> factualToolStates [
	<gtExample>
	| toolMessage row |
	toolMessage := GtLToolMessage new toolCall: (GtLFunctionToolCall new name: 'inspectLiveObject').
	row := BVCFairyToolActivityElement new messageViewModel: (GtLToolMessageViewModel new message: toolMessage).
	toolMessage beRunningExecutionState.
	self assert: (row activityText asLowercase includesSubstring: 'running').
	toolMessage beFinishedExecutionState.
	self assert: (row activityText asLowercase includesSubstring: 'finished').
	toolMessage beSkippedExecutionState.
	self assert: (row activityText asLowercase includesSubstring: 'skipped').
	self assert: row children size equals: 2.
	^ row
]

{ #category : 'examples' }
BVCFairyActivityExamples >> failureAndCancellationEvidence [
	<gtExample>
	| problem execution |
	problem := BVCFairyExamples new asynchronousFailureKeepsChild.
	self assert: problem failure == problem agentExecution responseMessage.
	self assert: problem agentExecution activityLabel equals: 'Failed / inspect original evidence'.
	execution := BVCFairyExamples new parentCancellation.
	self assert: execution activityLabel equals: 'Stop requested / cessation unverified'.
	execution observedOutcome: #returned.
	self assert: execution activityLabel equals: 'Stop requested / cessation unverified'.
	^ { problem. execution }
]

{ #category : 'examples' }
BVCFairyActivityExamples >> rebindAndRemoval [
	<gtExample>
	| firstModel secondModel row |
	firstModel := GtLToolMessageViewModel new message: (GtLToolMessage new toolCall: (GtLFunctionToolCall new name: 'first')).
	secondModel := GtLToolMessageViewModel new message: (GtLToolMessage new toolCall: (GtLFunctionToolCall new name: 'second')).
	row := BVCFairyToolActivityElement new messageViewModel: firstModel.
	row messageViewModel: secondModel.
	self assert: (firstModel announcer hasSubscriber: row) not.
	row unsubscribeFromMessageViewModel.
	self assert: (secondModel announcer hasSubscriber: row) not.
	row subscribeToMessageViewModel.
	row messageViewModel: secondModel.
	row updateElement; updateElement.
	self assert: row children size equals: 2.
	^ row
]

{ #category : 'examples' }
BVCFairyActivityExamples >> removalDisposesSubscriptions [
	<gtExample>
	^ BVCFairyWindowTitleExamples new evaluateOnUIProcess: [
		| row model space |
		model := GtLToolMessageViewModel new message: (GtLToolMessage new toolCall: (GtLFunctionToolCall new name: 'inspect')) .
		row := BVCFairyToolActivityElement new messageViewModel: model.
		space := BlSpace new.
		[ space root addChild: row.
		  row fireEvent: BlElementRemovedFromSceneGraphEvent new.
		  self assert: (model announcer hasSubscriber: row) not.
		  row fireEvent: BlElementAddedToSceneGraphEvent new.
		  self assert: (model announcer hasSubscriber: row).
		  row fireEvent: BlElementAddedToSceneGraphEvent new.
		  self assert: row children size equals: 2.
		  row
		] ensure: [ row removeFromParent. row unsubscribeFromMessageViewModel ] ]
]

{ #category : 'examples' }
BVCFairyActivityExamples >> returnedAndMissingMarkdown [
	<gtExample>
	| returned problem |
	returned := BVCFairyExamples new completedTask.
	self assert: returned activityLabel equals: 'Returned / acceptance unverified'.
	problem := BVCFairyExamples new missingMarkdown.
	self assert: problem agentExecution activityLabel equals: 'Failed / inspect original evidence'.
	^ { returned. problem }
]

{ #category : 'examples' }
BVCFairyActivityExamples >> timeoutDoesNotBecomeReturn [
	<gtExample>
	| parent child execution problem |
	parent := BVCFairyExamples new parentChat.
	child := GtLChat new provider: (BVCFairyProviderStub new shouldComplete: false).
	execution := BVCFairyAgentExecution new parentAgent: parent; agent: child.
	execution registerTerminationSignal.
	problem := execution waitUntilCompletionOrTimeoutAfter: 0.
	self assert: problem agentExecution == execution.
	self assert: (execution activityLabel includesSubstring: 'Timed out').
	execution observedOutcome: #returned.
	self assert: (execution activityLabel includesSubstring: 'Timed out').
	^ problem
]
