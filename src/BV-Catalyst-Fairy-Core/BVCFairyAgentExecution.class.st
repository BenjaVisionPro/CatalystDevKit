"
Links child cancellation and cleanup to its parent and rejects incomplete results.
"
Class {
	#name : 'BVCFairyAgentExecution',
	#superclass : 'GtLAgentExecution',
	#instVars : [
		'wasCancelled'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'execution' }
BVCFairyAgentExecution >> cancel [
	wasCancelled := true.
	self agent stopOngoingExecution.
	terminationSemaphore signal
]

{ #category : 'execution' }
BVCFairyAgentExecution >> createAgentResponse [
	| message content |
	message := self responseMessage.
	(message isKindOf: GtLErrorMessage) ifTrue: [
		^ self problem: 'Catalyst agent failed: ', message contentText ].
	(message notNil and: [ message respondsTo: #responseModels ]) ifFalse: [
		^ self problem: 'The Catalyst agent did not return a final response.' ].
	content := message responseModels at: 'Markdown' ifAbsent: [ nil ].
	content ifNil: [
		^ self problem: 'The Catalyst agent did not return Markdown content.' ].
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

{ #category : 'execution' }
BVCFairyAgentExecution >> onParentExecutionStateChanged: anAnnouncement [
	anAnnouncement state = GtLProviderState stopping ifTrue: [ self cancel ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> problem: aDescription [
	^ BVCFairyAgentProblem new
		description: aDescription;
		agentExecution: self;
		yourself
]

{ #category : 'execution' }
BVCFairyAgentExecution >> registerTerminationSignal [
	super registerTerminationSignal.
	self parentAgent announcer
		when: GtLChatExecutionStateChanged
		send: #onParentExecutionStateChanged:
		to: self.
	self parentAgent state = GtLProviderState stopping ifTrue: [ self cancel ]
]

{ #category : 'execution' }
BVCFairyAgentExecution >> signalCompletion [
	terminationSemaphore signal
]

{ #category : 'execution' }
BVCFairyAgentExecution >> unsubscribe [
	self agent announcer unsubscribe: terminationSemaphore.
	self parentAgent announcer unsubscribe: self
]

{ #category : 'execution' }
BVCFairyAgentExecution >> waitUntilCompletionOrTimeout [
	^ self waitUntilCompletionOrTimeoutAfter: 1200
]

{ #category : 'execution' }
BVCFairyAgentExecution >> waitUntilCompletionOrTimeoutAfter: seconds [
	| timedOut |
	[ timedOut := terminationSemaphore waitTimeoutSeconds: seconds ]
		ensure: [ self unsubscribe ].
	wasCancelled ifTrue: [
		^ self problem: 'The Catalyst agent was cancelled.' ].
	timedOut ifTrue: [
		self agent stopOngoingExecution.
		^ self problem: 'The Catalyst agent timed out; stop was requested.' ].
	^ nil
]
