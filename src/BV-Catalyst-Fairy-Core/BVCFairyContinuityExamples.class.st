"
Continuity examples use isolated volatile Lepiter databases; explicit persistence example uses the registered DevKit book.
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
BVCFairyContinuityExamples >> initialCheckpointFailureBlocksWork [
	<gtExample>
	| writer chat failed |
	writer := BVCFairyContinuityStub new database: LeDatabase new; failWrites: true.
	chat := BVCFairyChat new continuity: writer; provider: BVCFairyProviderStub new.
	failed := false.
	[ (BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest)
		startFromParentAgent: chat inContext: (GtLToolExecutionContext new currentChat: chat) ]
		on: Error do: [ :error | failed := error messageText includesSubstring: 'DEGRADED' ].
	self assert: failed.
	self assert: writer isDegraded.
	self assert: writer recordsPage children isEmpty.
	self assert: (writer contextString includesSubstring: 'DEGRADED').
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
	self assert: (chat instructions asString includesSubstring: 'Barry') .
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
