"
Starts one bounded Catalyst specialist through the existing GT harness.
"
Class {
	#name : 'BVCFairyAgentTool',
	#superclass : 'GtLToolForStartAgent',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyAgentTool >> description [
	^ 'Start one bounded Catalyst task and wait for its result. agentName must be "System Explorer" (source and documentation search) or "System Maintainer" (a change explicitly requested by the user). Supply prompt and taskDescription. Children use the current connection and model, start fresh, and cannot delegate. Omit toolNames or supply an empty list to use the role tools. A nonempty list selects a subset of those tools. Optional instructionPageReferences must identify existing pages. History forks and model changes are unsupported. Failures include the child execution id for inspection.'
]

{ #category : 'execution' }
BVCFairyAgentTool >> privatePerformToolCall: aToolCall inContext: anExecutionContext [
	| request parent builder execution executionError |
	[
		request := aToolCall arguments at: 'startAgentRequest'.
		parent := anExecutionContext currentChat.
		(parent isKindOf: BVCFairyChat)
			ifFalse: [ ^ GtLProblemDomainObject new description: 'Catalyst agents require a Catalyst Chat.' ].
		builder := BVCFairyAgentBuilder forAgentCreationRequest: request.
		builder validateForParent: parent ifErrorDo: [ :problem | ^ problem ].
		execution := builder startFromParentAgent: parent inContext: anExecutionContext.
		aToolCall at: #innerChat putRuntimeValue: execution agent.
		execution bindFeedbackToToolCall: aToolCall.
		executionError := execution waitUntilCompletionOrTimeout.
		executionError ifNotNil: [ ^ executionError ].
		^ execution createAgentResponse
	] on: Error do: [ :error |
		| failure |
		failure := GtLErrorMessage freeze: error.
		execution ifNotNil: [
			execution observedOutcome: #failed.
			[ execution agent stopOngoingExecution. execution unsubscribe ]
				on: Error do: [ :cleanupError | failure otherException: cleanupError ] ].
		^ BVCFairyAgentProblem new
			description: 'Catalyst delegation failed: ', error messageText, '. Partial image changes must be inspected before retrying.';
			agentExecution: execution;
			failure: failure;
			yourself ]
]
