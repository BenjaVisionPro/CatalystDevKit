"
Focused current-image checks for owner-aware inspection, sensitive metadata, mutation gating and bounded UI request races. Uses isolated chats/books except a temporary registered chat removed in ensure:.
"
Class {
	#name : 'BVCFairyRecoveryExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyRecoveryExamples >> blockedMaintainerStillAllowsInspection [
	<gtExample>
	| root request execution tool result builder |
	root := BVCFairyExamples new parentChat.
	root provider shouldComplete: false.
	request := BVCFairyExamples new explorerRequest agentName: 'System Maintainer'.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: request.
	execution := builder startFromParentAgent: root
		inContext: (GtLToolExecutionContext new currentChat: root; objectStorage: root objectStorage).
	[
		execution waitUntilCompletionOrTimeoutAfter: 0.
		self assert: (builder unfinishedMaintainerFor: root) == execution.
		tool := root tools items detect: [ :each | each name = 'inspectLiveObject' ].
		result := tool performToolCall: (self callForOwner: root inspectionId object: execution executionId path: '')
			inContext: (GtLToolExecutionContext new currentChat: root; objectStorage: root objectStorage).
		self assert: (result model data at: 'status') equals: 'observed'.
		self assert: (builder validateForParent: root ifErrorDo: [ :problem | problem ]) class equals: BVCFairyAgentProblem
	] ensure: [ execution agent provider privateExecutionState: GtLProviderState idle ].
	^ result
]

{ #category : 'private' }
BVCFairyRecoveryExamples >> callForOwner: ownerId object: objectId path: path [
	^ GtLFunctionToolCall new
		name: 'inspectLiveObject';
		rawArguments: (STONJSON toString: { 'ownerId' -> ownerId. 'objectId' -> objectId. 'slotPath' -> path } asDictionary)
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> cancellationAbandonsQueuedUiWork [
	<gtExample>
	| root execution universe request ran failed |
	root := BVCFairyExamples new parentChat.
	root provider shouldComplete: false.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: (BVCFairyExamples new explorerRequest agentName: 'System Maintainer'))
		startFromParentAgent: root inContext: (GtLToolExecutionContext new currentChat: root; objectStorage: root objectStorage).
	universe := BlUniverse new.
	ran := false.
	request := BVCFairyUIRequest new chat: execution agent; action: [ ran := true ]; submitOn: universe; yourself.
	[
		execution cancel.
		self assert: request state equals: #abandoned.
		request run.
		self assert: ran not.
		failed := false.
		[ request valueWithinMilliseconds: 100 ] on: Error do: [ :error | failed := error messageText includesSubstring: 'abandoned' ].
		self assert: failed.
		self assert: (BVCFairyUIRequest pending includes: request) not.
		self assert: (execution waitUntilCompletionOrTimeoutAfter: 0) class equals: BVCFairyAgentProblem
	] ensure: [ execution agent provider privateExecutionState: GtLProviderState idle ].
	^ request state
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> freshChatCannotBypassConflictingMaintainer [
	<gtExample>
	| registry owner fresh execution builder |
	registry := GtLChatRegistry current.
	owner := BVCFairyExamples new parentChat.
	fresh := BVCFairyExamples new parentChat.
	owner provider shouldComplete: false.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (BVCFairyExamples new explorerRequest agentName: 'System Maintainer').
	registry registerChat: owner.
	[
		execution := builder startFromParentAgent: owner
			inContext: (GtLToolExecutionContext new currentChat: owner; objectStorage: owner objectStorage).
		execution waitUntilCompletionOrTimeoutAfter: 0.
		self assert: (builder unfinishedMaintainerFor: fresh) == execution.
		self assert: (builder validateForParent: fresh ifErrorDo: [ :problem | problem ]) class equals: BVCFairyAgentProblem.
		self assert: (fresh tools anySatisfy: [ :tool | tool name = 'inspectLiveObject' ])
	] ensure: [
		execution ifNotNil: [ execution agent provider privateExecutionState: GtLProviderState idle ].
		registry removeChat: owner ].
	^ fresh
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> inspectionDoesNotRunApplicationCode [
	<gtExample>
	| root probe id result text |
	root := BVCFairyExamples new parentChat.
	probe := BVCFairyInspectionProbe new.
	id := root objectStorage addNewObject: probe.
	result := BVCFairyObjectInspection new inspectOwner: root inspectionId object: id path: '' from: root.
	self assert: (result data at: 'status') equals: 'observed'.
	text := STONJSON toString: result data.
	self assert: (text includesSubstring: 'DO-NOT-EXPOSE') not.
	self assert: probe accesses equals: 0.
	result := BVCFairyObjectInspection new inspectOwner: root inspectionId object: id path: 'value' from: root.
	self assert: ((result data at: 'snapshot') at: 'value') equals: 42.
	self assert: probe accesses equals: 0.
	result := BVCFairyObjectInspection new inspectOwner: root inspectionId object: id path: 'password' from: root.
	self assert: (result data at: 'status') equals: 'accessDenied'.
	self assert: probe accesses equals: 0.
	^ result
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> ownerQualifiedParentAndChildInspection [
	<gtExample>
	| root execution childId tool call result context |
	root := BVCFairyExamples new parentChat.
	execution := (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest)
		startFromParentAgent: root inContext: (GtLToolExecutionContext new currentChat: root; objectStorage: root objectStorage).
	self assert: execution waitUntilCompletionOrTimeout isNil.
	childId := execution agent objectStorage addNewObject: 42.
	tool := execution agent tools items detect: [ :each | each name = 'inspectLiveObject' ].
	self assert: tool rootChat == root.
	context := GtLToolExecutionContext new currentChat: execution agent; objectStorage: execution agent objectStorage.
	call := self callForOwner: root inspectionId, '/', execution executionId object: childId path: ''.
	result := tool performToolCall: call inContext: context.
	self assert: ((result model data at: 'snapshot') at: 'value') equals: 42.
	call := self callForOwner: root inspectionId object: execution executionId path: ''.
	result := tool performToolCall: call inContext: context.
	self assert: ((result model data at: 'snapshot') at: 'executionId') equals: execution executionId.
	self assert: (execution agent tools items noneSatisfy: [ :each | each name = 'smalltalkCodeEvaluation' ]).
	^ result
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> processAndContextInspectionIsBounded [
	<gtExample>
	| root id result |
	root := BVCFairyExamples new parentChat.
	id := root objectStorage addNewObject: Processor activeProcess.
	result := BVCFairyObjectInspection new inspectOwner: root inspectionId object: id path: '' from: root.
	self assert: ((result data at: 'snapshot') at: 'frames') size <= 12.
	id := root objectStorage addNewObject: thisContext.
	result := BVCFairyObjectInspection new inspectOwner: root inspectionId object: id path: '' from: root.
	self assert: ((result data at: 'snapshot') at: 'frames') size <= 12.
	self assert: ((result data at: 'snapshot') keys includes: 'receiver') not.
	^ result
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> referenceFailuresAndBounds [
	<gtExample>
	| root objectId inspect result |
	root := BVCFairyExamples new parentChat.
	objectId := root objectStorage addNewObject: (Array new: 30 withAll: 'hidden string').
	inspect := [ :owner :id :path | BVCFairyObjectInspection new inspectOwner: owner object: id path: path from: root ].
	result := inspect value: 'expired-owner' value: objectId value: ''.
	self assert: (result data at: 'status') equals: 'ownerUnavailable'.
	result := inspect value: root inspectionId value: UUID new asString value: ''.
	self assert: (result data at: 'status') equals: 'objectMissing'.
	result := inspect value: root inspectionId value: '?*' value: ''.
	self assert: (result data at: 'status') equals: 'invalidReference'.
	result := inspect value: root inspectionId value: objectId value: 'a/b/c/d'.
	self assert: (result data at: 'status') equals: 'pathLimitExceeded'.
	result := inspect value: root inspectionId value: objectId value: ''.
	self assert: ((result data at: 'snapshot') at: 'items') size equals: 12.
	self assert: ((STONJSON toString: result data) includesSubstring: 'hidden string') not.
	25 timesRepeat: [ root objectStorage addNewObject: 1 ].
	result := inspect value: root inspectionId value: '' value: ''.
	self assert: (result data at: 'objects') size equals: 20.
	^ result
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> runningUiWorkKeepsMutationGateClosed [
	<gtExample>
	| root execution request universe entered release done worker failed partial builder |
	root := BVCFairyExamples new parentChat.
	root provider shouldComplete: false.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: (BVCFairyExamples new explorerRequest agentName: 'System Maintainer').
	execution := builder startFromParentAgent: root inContext:
		(GtLToolExecutionContext new currentChat: root; objectStorage: root objectStorage).
	execution waitUntilCompletionOrTimeoutAfter: 0.
	execution agent provider privateExecutionState: GtLProviderState idle.
	universe := BlUniverse new.
	entered := Semaphore new. release := Semaphore new. done := Semaphore new.
	partial := Array with: 0.
	request := BVCFairyUIRequest new
		chat: execution agent;
		action: [ partial at: 1 put: 1. entered signal. release wait. partial at: 1 put: 2 ];
		submitOn: universe;
		yourself.
	worker := [ [ request run ] ensure: [ done signal ] ] fork.
	[
		self assert: (entered waitTimeoutMilliseconds: 1000) not.
		failed := false.
		[ request valueWithinMilliseconds: 10 ] on: Error do: [ :error | failed := error messageText includesSubstring: 'still outstanding' ].
		self assert: failed.
		self assert: request state equals: #running.
		self assert: partial first equals: 1.
		self assert: (builder unfinishedMaintainerFor: root) == execution.
		release signal.
		self assert: (done waitTimeoutMilliseconds: 1000) not.
		self assert: request state equals: #finished.
		self assert: partial first equals: 2.
		self assert: (builder unfinishedMaintainerFor: root) isNil
	] ensure: [ release signal. universe undefer: (request instVarNamed: 'callback') ].
	^ partial
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> uiErrorPreservesOriginalException [
	<gtExample>
	| universe request original caught |
	universe := BlUniverse new.
	original := Error new messageText: 'Original UI failure'.
	request := BVCFairyUIRequest action: [ original signal ] on: universe.
	request run.
	caught := nil.
	[ request valueWithinMilliseconds: 100 ] on: Error do: [ :error | caught := error ].
	self assert: caught == original.
	self assert: request state equals: #finished.
	self assert: (BVCFairyUIRequest pending includes: request) not.
	universe undefer: (request instVarNamed: 'callback').
	^ caught messageText
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> uiThreadUsesDirectExecution [
	<gtExample>
	| result |
	result := BVCFairyWindowTitleExamples new evaluateOnUIProcess: [
		| before value |
		before := BVCFairyUIRequest pending size.
		value := BVCFairyWindowTitleExamples new evaluateOnUIProcess: [ 42 ].
		self assert: BVCFairyUIRequest pending size equals: before.
		value ].
	self assert: result equals: 42.
	^ result
]

{ #category : 'examples' }
BVCFairyRecoveryExamples >> unservicedUiCallbackIsAbandoned [
	<gtExample>
	| universe request ran failed started |
	universe := BlUniverse new.
	ran := false.
	request := BVCFairyUIRequest action: [ ran := true ] on: universe.
	started := Time millisecondClockValue.
	failed := false.
	[ request valueWithinMilliseconds: 10 ] on: Error do: [ :error |
		failed := error messageText includesSubstring: 'before starting' ].
	self assert: failed.
	self assert: Time millisecondClockValue - started < 2000.
	self assert: request state equals: #abandoned.
	request run.
	self assert: ran not.
	self assert: (BVCFairyUIRequest pending includes: request) not.
	self assert: (universe instVarNamed: 'deferredActions') size equals: 0.
	^ request state
]
