"Adapts the GT harness to two bounded Catalyst roles. Rejects unsupported options rather than silently ignoring them."
Class {
	#name : #BVCFairyAgentBuilder,
	#superclass : #GtLAgentExecutionBuilder,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCFairyAgentBuilder >> request [
	"Keep the upstream legacy spelling out of the Catalyst API."
	^ super agentCreationReauest
]

{ #category : #accessing }
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

{ #category : #validation }
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
	^ nil
]

{ #category : #running }
BVCFairyAgentBuilder >> createAgentForParent: aParent [
	| child tools |
	child := self createNewStandaloneChatFrom: aParent.
	tools := self roleTools.
	(self request toolNames ifNil: [ #() ]) ifNotEmpty: [ :toolNames |
		tools := GtLTools withAll: (tools select: [ :tool | toolNames includes: tool name ]) ].
	child tools: tools.
	aParent devKitContext configureChat: child forRole: self request agentName.
	(self request instructionPageReferences ifNil: [ #() ]) do: [ :reference |
		child pageObjectExplanation: (self locatePageForReference: reference) ].
	^ child
]

{ #category : #running }
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
	[ execution isCancelled ifFalse: [ child sendMarkdown: self request prompt ].
	  aParent state = GtLProviderState stopping ifTrue: [ execution cancel ] ]
		on: Error do: [ :error |
			child stopOngoingExecution.
			child ensureReplyMessage.
			child addErrorMessage: (GtLErrorMessage freeze: error).
			execution signalCompletion ].
	^ execution
]
