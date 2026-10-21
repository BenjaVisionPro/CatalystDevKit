"
Recovery examples use isolated volatile Lepiter databases and controlled providers. They do not establish disk, crash or rebuild durability.
"
Class {
	#name : 'BVCFairyContinuityExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyContinuityExamples >> boundsAndLoad [
	<gtExample>
	| writer requestId loaded |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	40 timesRepeat: [
		requestId := writer startKind: 'root' parentId: nil.
		writer recordId: requestId outcome: 'provider finished; acceptance unverified'.
		writer recordId: requestId outcome: 'duplicate ignored' ].
	self assert: writer recordsPage children size equals: 32.
	self assert: (writer recordsPage children last string includesSubstring: 'duplicate') not.
	loaded := BVCFairyContinuityStub new database: writer database.
	self assert: loaded contextString equals: writer contextString.
	self assert: loaded contextString size < 4200.
	^ loaded
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> checkpointFailureReleasesLock [
	<gtExample>
	| writer entered |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	self assert: (writer checkpoint: [ 1 / 0 ]) not.
	self assert: writer lastFailure exception class equals: ZeroDivide.
	entered := false.
	self assert: (writer checkpoint: [ entered := true ]).
	self assert: entered.
	self assert: writer isDegraded.
	self assert: (writer contextString includesSubstring: 'DEGRADED').
	^ writer
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> childLifecycle [
	<gtExample>
	| writer chat execution context |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyProviderStub new.
	context := GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest)
		startFromParentAgent: chat inContext: context.
	self assert: execution waitUntilCompletionOrTimeout isNil.
	self assert: (writer recordsPage children first string includesSubstring: 'child provider finished').
	self assert: (execution agent announcer hasSubscriber: execution) not.
	self assert: (chat announcer hasSubscriber: execution) not.
	^ execution
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> childResultIncludesCheckpointFailure [
	<gtExample>
	| chat writer execution result original |
	chat := BVCFairyExamples new parentChat.
	writer := chat continuity.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest)
		startFromParentAgent: chat
		inContext: (GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage).
	original := execution responseMessage.
	writer failWrites: true.
	self assert: execution waitUntilCompletionOrTimeout isNil.
	result := execution createAgentResponse.
	self assert: result class equals: GtLAgentExecutionResult.
	self assert: (result content content includesSubstring: 'Task complete.').
	self assert: (result content content includesSubstring: 'Continuity checkpoint failed').
	self assert: execution responseMessage == original.
	self assert: (original responseModels at: 'Markdown') content equals: 'Task complete.'.
	self assert: writer lastFailure contentText equals: 'Controlled persistence failure'.
	self assert: (chat announcer hasSubscriber: execution) not.
	^ result
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> completionFailurePreservesResponse [
	<gtExample>
	| writer chat response otherSubscription |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	chat := BVCFairyExamples new parentChat continuity: writer.
	otherSubscription := chat announcer
		when: GtLThreadRunIsDoneAnnouncement do: [ ] for: chat.
	chat provider shouldComplete: false.
	chat sendMarkdown: 'Start once'.
	self assert: chat continuityRequestId notNil.
	writer failWrites: true.
	response := BVCFairyResponseStub new responseModels:
		(Dictionary new at: 'Markdown' put: (GtLMarkdown content: 'Original work result'); yourself).
	chat addAssistantMessage: response.
	chat provider privateExecutionState: GtLProviderState idle.
	self assert: chat allMessages last == response.
	self assert: writer isDegraded.
	self assert: writer lastFailure contentText equals: 'Controlled persistence failure'.
	self assert: chat continuityRequestId isNil.
	self assert: (chat announcer hasSubscriber: chat).
	chat announcer removeSubscription: otherSubscription.
	self assert: (chat announcer hasSubscriber: chat) not.
	writer failWrites: false.
	chat provider shouldComplete: true.
	chat sendMarkdown: 'Continue after repair'.
	self assert: writer isDegraded not.
	self assert: (chat allMessages select: #isUserRole) size equals: 2.
	self assert: writer recordsPage children size equals: 2.
	self assert: (writer recordsPage children last string includesSubstring: 'provider finished').
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> contextFailureAllowsChat [
	<gtExample>
	| writer chat |
	writer := BVCFairyContinuityStub new.
	chat := BVCFairyExamples new parentChat continuity: writer.
	chat sendMarkdown: 'Diagnose the missing continuity database'.
	self assert: writer isDegraded.
	self assert: writer lastFailure exception class equals: MessageNotUnderstood.
	self assert: (chat instructions instructionString includesSubstring: 'context unavailable').
	self assert: chat allMessages last class equals: BVCFairyResponseStub.
	writer database: LeDatabase new.
	chat sendMarkdown: 'Continue after restoring the database'.
	self assert: writer isDegraded not.
	self assert: writer recordsPage children size equals: 1.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> degradedContinuityAllowsDiagnosis [
	<gtExample>
	| writer chat execution |
	writer := BVCFairyContinuityStub new database: LeDatabase new; failWrites: true.
	chat := BVCFairyExamples new parentChat continuity: writer.
	chat sendMarkdown: 'Diagnose without starting mutating work'.
	self assert: writer isDegraded.
	self assert: chat continuityRequestId isNil.
	self assert: (chat instructions instructionString includesSubstring: 'DEGRADED').
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest)
		startFromParentAgent: chat
		inContext: (GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage).
	self assert: execution waitUntilCompletionOrTimeout isNil.
	self assert: execution createAgentResponse class equals: GtLAgentExecutionResult.
	self assert: (execution agent tools anySatisfy: [ :tool | tool name = 'compileMethods' ]) not.
	self assert: (chat announcer hasSubscriber: execution) not.
	writer failWrites: false.
	chat sendMarkdown: 'Continue once checkpoint storage is repaired'.
	self assert: writer isDegraded not.
	self assert: (chat instructions instructionString includesSubstring: 'initial continuity checkpoint succeeded').
	self assert: writer recordsPage children size equals: 1.
	self assert: (chat allMessages select: #isUserRole) size equals: 2.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> delegationExceptionCanRecover [
	<gtExample>
	| chat writer context call result problem |
	chat := BVCFairyExamples new parentChat.
	writer := chat continuity.
	context := GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage.
	"Simulate a broken continuity extension at the delegation boundary."
	chat continuity: Object new.
	call := GtLFunctionToolCall new name: 'startAgent';
		rawArguments: '{"startAgentRequest":{"agentName":"System Explorer","prompt":"Read only.","taskDescription":"Diagnose"}}'.
	result := BVCFairyAgentTool new performToolCall: call inContext: context.
	problem := result model.
	self assert: problem class equals: BVCFairyAgentProblem.
	self assert: problem failure exception class equals: MessageNotUnderstood.
	self assert: call result == result.
	self assert: chat objectStorage objectIds isEmpty.
	chat continuity: writer.
	call := GtLFunctionToolCall new name: 'startAgent';
		rawArguments: '{"startAgentRequest":{"agentName":"System Explorer","prompt":"Read only.","taskDescription":"Continue after repair"}}'.
	result := BVCFairyAgentTool new performToolCall: call inContext: context.
	self assert: result model class equals: GtLAgentExecutionResult.
	self assert: chat objectStorage objectIds size equals: 1.
	self assert: writer recordsPage children size equals: 1.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> initialCheckpointFailureBlocksWork [
	<gtExample>
	| writer chat execution problem request |
	writer := BVCFairyContinuityStub new database: LeDatabase new; failWrites: true.
	chat := BVCFairyExamples new parentChat continuity: writer.
	request := BVCFairyExamples new explorerRequest agentName: 'System Maintainer'.
	execution := (BVCFairyAgentBuilderStub forAgentCreationRequest: request)
		startFromParentAgent: chat inContext: (GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage).
	self assert: execution waitUntilCompletionOrTimeout isNil.
	problem := execution createAgentResponse.
	self assert: problem class equals: BVCFairyAgentProblem.
	self assert: (problem description includesSubstring: 'not started').
	self assert: problem failure exception class equals: Error.
	self assert: (execution agent allMessages noneSatisfy: #isUserRole).
	self assert: execution agent state equals: GtLProviderState idle.
	self assert: writer isDegraded.
	self assert: writer lastFailure contentText equals: 'Controlled persistence failure'.
	self assert: writer recordsPage children isEmpty.
	self assert: (writer contextString includesSubstring: 'DEGRADED').
	self assert: (chat announcer hasSubscriber: execution) not.
	^ problem
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> instructionRefreshBoundsOversizedState [
	<gtExample>
	| writer statePage chat context instructions |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	7 timesRepeat: [ writer startKind: 'root' parentId: nil ].
	statePage := writer database pageNamed: 'Barry workstream state'.
	statePage addSnippet: (LeTextSnippet string: (String new: 5000 withAll: $x)).
	statePage addSnippet: (LeTextSnippet string: 'Controlled omitted tail').
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyProviderStub new.
	chat refreshInstructions.
	context := writer contextString.
	instructions := chat instructions instructionString.
	self assert: context size <= 8192.
	self assert: (instructions includesSubstring: context).
	self assert: (instructions includesSubstring: '[Omitted/truncated state; read [[Barry workstream state]]').
	self assert: (context includesSubstring: 'Controlled omitted tail') not.
	self assert: (context includesSubstring: writer recordsPage children first string) not.
	(writer recordsPage children asArray last: 6) do: [ :snippet |
		self assert: (context includesSubstring: snippet string) ].
	self assert: writer database hasMonitor not.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> instructionRefreshRecoversMultipleStateSnippets [
	<gtExample>
	| writer statePage fields chat instructions |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	statePage := writer database ensurePageNamed: 'Barry workstream state'.
	fields := #('Goal: controlled recovery goal' 'Decisions: controlled existing path' 'Implementation state: controlled image change' 'Verification: controlled fresh checks' 'Delivery state: controlled unpublished source' 'Remaining gaps: controlled durability gap' 'Next action: controlled parent review').
	fields do: [ :field | statePage addSnippet: (LeTextSnippet string: field) ].
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyProviderStub new.
	chat refreshInstructions.
	instructions := chat instructions instructionString.
	fields do: [ :field | self assert: (instructions includesSubstring: field) ].
	self assert: (instructions includesSubstring: writer contextString).
	self assert: (instructions includesSubstring: 'Omitted/truncated state') not.
	self assert: writer database hasMonitor not.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> rootLifecycle [
	<gtExample>
	| writer chat firstRecord |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyProviderStub new.
	chat sendMarkdown: 'Do not persist this raw message'.
	self assert: writer recordsPage children size equals: 1.
	firstRecord := writer recordsPage children first string.
	self assert: (firstRecord includesSubstring: 'provider finished').
	self assert: (firstRecord includesSubstring: 'Do not persist') not.
	self assert: chat continuityRequestId isNil.
	chat provider privateExecutionState: GtLProviderState idle.
	chat signalRunIsDone.
	self assert: writer recordsPage children first string equals: firstRecord.
	chat sendMarkdown: 'Next request'.
	self assert: writer recordsPage children size equals: 2.
	self assert: (chat instructions instructionString includesSubstring: 'Barry') .
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> rootSendFailure [
	<gtExample>
	| writer chat failed |
	writer := BVCFairyContinuityStub new database: LeDatabase new.
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyFailingProviderStub new.
	failed := false.
	[ chat sendMarkdown: 'Fail' ] on: Error do: [ :error | failed := true ].
	self assert: failed.
	self assert: (writer recordsPage children first string includesSubstring: 'send failed').
	self assert: chat continuityRequestId isNil.
	^ chat
]

{ #category : 'examples' }
BVCFairyContinuityExamples >> timeoutPreservesResultAndBlocksOverlappingMaintainer [
	<gtExample>
	| chat writer request execution problem builder nextExecution originalMessages |
	chat := BVCFairyExamples new parentChat.
	writer := chat continuity.
	request := BVCFairyExamples new explorerRequest agentName: 'System Maintainer'.
	chat provider shouldComplete: false.
	builder := BVCFairyAgentBuilderStub forAgentCreationRequest: request.
	execution := builder startFromParentAgent: chat inContext: (GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage).
	[
		originalMessages := execution agent allMessages size.
		writer failWrites: true.
		problem := execution waitUntilCompletionOrTimeoutAfter: 0.
		self assert: (problem description includesSubstring: 'timed out').
		self assert: writer isDegraded.
		self assert: (chat announcer hasSubscriber: execution) not.
		self assert: (execution agent announcer hasSubscriber: execution) not.
		problem := builder validateForParent: chat ifErrorDo: [ :failure | failure ].
		self assert: problem class equals: BVCFairyAgentProblem.
		self assert: problem agentExecution == execution.
		execution agent provider privateExecutionState: GtLProviderState idle.
		self assert: (builder validateForParent: chat ifErrorDo: [ :failure | failure ]) isNil.
		writer failWrites: false.
		chat provider shouldComplete: true.
		nextExecution := builder startFromParentAgent: chat inContext: (GtLToolExecutionContext new currentChat: chat; objectStorage: chat objectStorage).
		self assert: nextExecution waitUntilCompletionOrTimeout isNil.
		self assert: nextExecution createAgentResponse class equals: GtLAgentExecutionResult.
		self assert: execution agent allMessages size equals: originalMessages.
		self assert: chat objectStorage objectIds size equals: 2
	] ensure: [ execution agent provider privateExecutionState: GtLProviderState idle ].
	^ chat
]
