"Starts one bounded Catalyst specialist through the existing GT harness."
Class {
	#name : #BVCFairyAgentTool,
	#superclass : #GtLToolForStartAgent,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCFairyAgentTool >> description [
	^ 'Start one bounded Catalyst task and wait for its result. agentName must be "System Explorer" (source and documentation search) or "System Maintainer" (a change explicitly requested by the user). Supply prompt and taskDescription. Children use the current connection and model, start fresh, and cannot delegate. Omit toolNames to use the role tools. If supplied, toolNames must be a nonempty subset of those tools. Optional instructionPageReferences must identify existing pages. History forks and model changes are unsupported. Failures include the child execution id for inspection.'
]

{ #category : #private }
BVCFairyAgentTool >> privatePerformToolCall: aToolCall inContext: anExecutionContext [
	| request parent builder execution executionError |
	request := aToolCall arguments at: 'startAgentRequest'.
	parent := anExecutionContext currentChat.
	(parent isKindOf: BVCFairyChat)
		ifFalse: [ ^ GtLProblemDomainObject new description: 'Catalyst agents require a Catalyst Chat.' ].
	builder := BVCFairyAgentBuilder forAgentCreationRequest: request.
	builder validateForParent: parent ifErrorDo: [ :problem | ^ problem ].
	execution := builder startFromParentAgent: parent inContext: anExecutionContext.
	aToolCall at: #innerChat putRuntimeValue: execution agent.
	executionError := execution waitUntilCompletionOrTimeout.
	executionError ifNotNil: [ ^ executionError ].
	^ execution createAgentResponse
]
