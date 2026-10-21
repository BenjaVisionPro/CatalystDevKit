"
Adapts the GT harness to two bounded Catalyst roles. Rejects unsupported options rather than silently ignoring them.
"
Class {
	#name : 'BVCFairyAgentBuilder',
	#superclass : 'GtLAgentExecutionBuilder',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'building' }
BVCFairyAgentBuilder >> createAgentForParent: aParent [
	| child tools |
	child := self createNewStandaloneChatFrom: aParent.
	(child provider isKindOf: GtLModelProvider) ifTrue: [
		child provider model copy provider: child provider.
		child provider compactionStrategy: child provider compactionStrategy copy ].
	tools := self roleTools.
	(self request toolNames ifNil: [ #() ]) ifNotEmpty: [ :toolNames |
		tools := GtLTools withAll: (tools select: [ :tool | toolNames includes: tool name ]) ].
	tools do: [ :tool | (tool isKindOf: BVCFairyObjectInspectionTool) ifTrue: [ tool rootChat: aParent ] ].
	child tools: tools.
	aParent devKitContext configureChat: child forRole: self request agentName.
	child instruction: aParent continuity contextString titled: 'Barry work continuity'.
	(self request instructionPageReferences ifNil: [ #() ]) do: [ :reference |
		child pageObjectExplanation: (self locatePageForReference: reference) ].
	^ child
]

{ #category : 'validation' }
BVCFairyAgentBuilder >> mutationOwnershipRootsFor: aParent [
	| roots |
	roots := OrderedCollection with: aParent.
	(GtLChatRegistry current chats select: [ :chat | chat isKindOf: BVCFairyChat ]) do: [ :chat |
		(roots includes: chat) ifFalse: [ roots add: chat ] ].
	^ roots
]

{ #category : 'accessing' }
BVCFairyAgentBuilder >> request [
	"Keep the upstream legacy spelling out of the Catalyst API."
	^ super agentCreationReauest
]

{ #category : 'accessing' }
BVCFairyAgentBuilder >> roleTools [
	| tools |
	tools := BVCDevKitContext readOnlyTools.
	self request agentName = 'System Maintainer' ifTrue: [
		tools addAll: GtLTools gtCodeChange.
		tools addAll: GtLTools leChange.
		tools addAll: GtLTools gtExamplesRun.
		tools addAll: GtLTools testRun.
		tools addAll: GtLTools gtObjectsExecution ].
	^ tools
]

{ #category : 'building' }
BVCFairyAgentBuilder >> startFromParentAgent: aParent inContext: aContext [
	| child execution |
	self validateForParent: aParent ifErrorDo: [ :problem | self error: problem description ].
	child := self createAgentForParent: aParent.
	execution := BVCFairyAgentExecution new
		agent: child;
		parentAgent: aParent;
		initialRequest: self request;
		yourself.
	aContext objectStorage ifNotNil: [ :storage |
		execution executionId: (storage addNewObject: execution) ].
	execution registerTerminationSignal.
	[ execution startContinuity.
	  execution isCancelled ifFalse: [ child sendMarkdown: self request prompt ].
	  aParent state = GtLProviderState stopping ifTrue: [ execution cancel ] ]
		on: Error do: [ :error |
			child state = GtLProviderState idle ifFalse: [ child stopOngoingExecution ].
			child ensureReplyMessage.
			child addErrorMessage: (GtLErrorMessage freeze: error).
			execution signalCompletion ].
	^ execution
]

{ #category : 'validation' }
BVCFairyAgentBuilder >> unfinishedMaintainerFor: aParent [
	(self mutationOwnershipRootsFor: aParent) do: [ :root |
		root objectStorage objectIds do: [ :identifier |
			| object |
			object := root objectStorage objectAt: identifier.
			((object isKindOf: BVCFairyAgentExecution) and: [
				object initialRequest agentName = 'System Maintainer' and: [ object hasLiveMutationOwnership ] ])
				ifTrue: [ ^ object ] ] ].
	^ nil
]

{ #category : 'validation' }
BVCFairyAgentBuilder >> validateForParent: aParent ifErrorDo: anErrorBlock [
	| modelName |
	#(agentName prompt taskDescription) do: [ :selector |
		| value |
		value := self request perform: selector.
		(value isString and: [ value trimBoth notEmpty ]) ifFalse: [
			^ anErrorBlock value: (GtLMissingDomainObject new objectName: selector asString) ] ].
	(#('System Explorer' 'System Maintainer') includes: self request agentName)
		ifFalse: [ ^ anErrorBlock value: (GtLProblemDomainObject new description: 'Unknown Catalyst agent role.') ].
	self request shouldForkCurrentAgent = true
		ifTrue: [ ^ anErrorBlock value: (GtLProblemDomainObject new description: 'Catalyst agents start with a fresh conversation.') ].
	modelName := self request modelName.
	(modelName notNil and: [ modelName notEmpty ]) ifTrue: [
		((aParent provider respondsTo: #modelName) and: [ aParent provider modelName = modelName ])
			ifFalse: [ ^ anErrorBlock value: (GtLProblemDomainObject new description: 'Catalyst agents use the parent connection and model.') ] ].
	(self request toolNames ifNil: [ #() ]) do: [ :name |
		(self roleTools anySatisfy: [ :tool | tool name = name ]) ifFalse: [
			^ anErrorBlock value: (GtLProblemDomainObject new description: 'Tool is outside the Catalyst role: ', name) ] ].
	(self request instructionPageReferences ifNil: [ #() ]) do: [ :reference |
		(self locatePageForReference: reference) ifNil: [
			^ anErrorBlock value: (GtLProblemDomainObject new description: 'Instruction page or database not found.') ] ].
	aParent state = GtLProviderState stopping ifTrue: [
		^ anErrorBlock value: (GtLProblemDomainObject new description: 'The parent chat is stopping.') ].
	self request agentName = 'System Maintainer' ifTrue: [
		(self unfinishedMaintainerFor: aParent) ifNotNil: [ :execution |
			^ anErrorBlock value: (execution problem: 'Maintainer ', execution executionId asString,
				' retains live mutation ownership: provider ', execution agent state class name,
				', pending Barry UI: ', (BVCFairyUIRequest hasPendingForChat: execution agent) asString,
				'. Preserve this owner. Historical unknown outcomes alone do not block a new task; missing observations do not clear live ownership.') ] ].
	^ nil
]
