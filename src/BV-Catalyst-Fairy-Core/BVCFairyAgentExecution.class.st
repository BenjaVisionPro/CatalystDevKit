"
Links child cancellation and cleanup to its parent and rejects incomplete results.
"
Class {
	#name : 'BVCFairyAgentExecution',
	#superclass : 'GtLAgentExecution',
	#instVars : [
		'wasCancelled',
		'continuityRequestId',
		'feedbackMessage',
		'observedOutcome'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'feedback' }
BVCFairyAgentExecution >> activityLabel [
	observedOutcome = #returned ifTrue: [ ^ 'Returned / acceptance unverified' ].
	observedOutcome = #failed ifTrue: [ ^ 'Failed / inspect original evidence' ].
	observedOutcome = #timedOut ifTrue: [ ^ 'Timed out / stop requested / cessation unverified' ].
	(observedOutcome = #stopRequested or: [ wasCancelled ]) ifTrue: [ ^ 'Stop requested / cessation unverified' ].
	^ 'Observed provider: ', self agent state class name, ' / acceptance unverified'
]

{ #category : 'feedback' }
BVCFairyAgentExecution >> bindFeedbackToToolCall: aToolCall [
	aToolCall at: #catalystAgentExecution putRuntimeValue: self.
	feedbackMessage := self parentAgent ensureReplyMessage executionMessages
		detect: [ :message | (message isKindOf: GtLToolMessage) and: [ message toolCall == aToolCall ] ]
		ifNone: [ nil ].
	self notifyFeedbackChanged
]

{ #category : 'execution' }
BVCFairyAgentExecution >> cancel [
	wasCancelled := true.
	self observedOutcome: #stopRequested.
	self agent stopOngoingExecution.
	BVCFairyUIRequest abandonQueuedForChat: self agent.
	terminationSemaphore signal
]

{ #category : 'continuity' }
BVCFairyAgentExecution >> continuityWarning [
	| writer |
	self parentAgent ifNil: [ ^ '' ].
	writer := self parentAgent continuity.
	writer isDegraded ifFalse: [ ^ '' ].
	^ 'Continuity checkpoint failed; the child result is preserved, but its checkpoint is unverified. Do not repeat mutating work. Inspect parent continuity lastFailure and partial state.'
]

{ #category : 'execution' }
BVCFairyAgentExecution >> createAgentResponse [
	| message content warning |
	message := self responseMessage.
	(message isKindOf: GtLErrorMessage) ifTrue: [
		self observedOutcome: #failed.
		^ (self problem: 'Catalyst agent failed: ', message contentText)
			failure: message; yourself ].
	(message notNil and: [ message respondsTo: #responseModels ]) ifFalse: [
		self observedOutcome: #failed.
		^ self problem: 'The Catalyst agent did not return a final response.' ].
	content := message responseModels at: 'Markdown' ifAbsent: [ nil ].
	content ifNil: [
		self observedOutcome: #failed.
		^ self problem: 'The Catalyst agent did not return Markdown content.' ].
	warning := self continuityWarning.
	warning ifNotEmpty: [
		content := GtLMarkdown content: content content, String cr, String cr, warning ].
	self observedOutcome: #returned.
	^ GtLAgentExecutionResult new
		agentExecutionId: self executionId;
		agentExecution: self;
		parentAgent: self parentAgent;
		request: self initialRequest;
		content: content;
		yourself
]

{ #category : 'initialization' }
BVCFairyAgentExecution >> initialize [
	super initialize.
	wasCancelled := false
]

{ #category : 'testing' }
BVCFairyAgentExecution >> isCancelled [
	^ wasCancelled
]

{ #category : 'feedback' }
BVCFairyAgentExecution >> notifyFeedbackChanged [
	feedbackMessage ifNotNil: [ :message |
		message announce: (GtLMessageContentsChanged new message: message) ]
]

{ #category : 'feedback' }
BVCFairyAgentExecution >> observedOutcome: aSymbol [
	"Terminal observations are sticky; a late provider event cannot imply acceptance."
	(#(returned failed stopRequested timedOut) includes: observedOutcome) ifTrue: [ ^ self ].
	observedOutcome := aSymbol.
	self notifyFeedbackChanged
]

{ #category : 'execution' }
BVCFairyAgentExecution >> onChildExecutionStateChanged: anAnnouncement [
	self notifyFeedbackChanged.
	anAnnouncement state = GtLProviderState idle ifTrue: [ terminationSemaphore signal ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> onParentExecutionStateChanged: anAnnouncement [
	anAnnouncement state = GtLProviderState stopping ifTrue: [ self cancel ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> problem: aDescription [
	^ BVCFairyAgentProblem new
		description: aDescription, String cr, self continuityWarning;
		failure: (self parentAgent ifNotNil: [ :parent | parent continuity lastFailure ]);
		agentExecution: self;
		yourself
]

{ #category : 'continuity' }
BVCFairyAgentExecution >> recordContinuity: anOutcome [
	continuityRequestId ifNotNil: [ self parentAgent continuity recordId: continuityRequestId outcome: anOutcome ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> registerTerminationSignal [
	terminationSemaphore := Semaphore new.
	self agent announcer when: GtLChatExecutionStateChanged send: #onChildExecutionStateChanged: to: self.
	self parentAgent announcer when: GtLChatExecutionStateChanged send: #onParentExecutionStateChanged: to: self.
	self parentAgent state = GtLProviderState stopping ifTrue: [ self cancel ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> signalCompletion [
	terminationSemaphore signal
]

{ #category : 'continuity' }
BVCFairyAgentExecution >> startContinuity [
	continuityRequestId := self parentAgent continuity
		startKind: 'child'
		parentId: self parentAgent continuityRequestId.
	(continuityRequestId isNil and: [ self initialRequest agentName = 'System Maintainer' ])
		ifTrue: [ self error: 'Continuity checkpoint failed; Maintainer work was not started. Read-only diagnosis remains available. Inspect parent continuity lastFailure.' ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> unsubscribe [
	self agent announcer unsubscribe: self.
	self parentAgent announcer unsubscribe: self
]

{ #category : 'execution' }
BVCFairyAgentExecution >> waitUntilCompletionOrTimeout [
	^ self waitUntilCompletionOrTimeoutAfter: 1200
]

{ #category : 'execution' }
BVCFairyAgentExecution >> waitUntilCompletionOrTimeoutAfter: seconds [
	| timedOut |
	[ timedOut := terminationSemaphore waitTimeoutSeconds: seconds ] ensure: [ self unsubscribe ].
	wasCancelled ifTrue: [
		self observedOutcome: #stopRequested.
		self recordContinuity: 'cancel requested; child cessation and partial image changes unknown; late completion not observed; acceptance unverified'.
		^ self problem: 'The Catalyst agent was cancelled.' ].
	timedOut ifTrue: [
		self observedOutcome: #timedOut.
		self agent stopOngoingExecution.
		BVCFairyUIRequest abandonQueuedForChat: self agent.
		self recordContinuity: 'timeout; stop requested; child cessation and partial image changes unknown; late completion not observed; acceptance unverified'.
		^ self problem: 'The Catalyst agent timed out; stop was requested.' ].
	self recordContinuity: ((self responseMessage isKindOf: GtLErrorMessage)
		ifTrue: [ 'child response error; partial image changes unknown; acceptance unverified' ]
		ifFalse: [ 'child provider finished; task success unknown; acceptance unverified' ]).
	^ nil
]
