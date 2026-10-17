"A delegation failure with the original diagnostic and the child execution available for inspection."
Class {
	#name : #BVCFairyAgentProblem,
	#superclass : #GtLProblemDomainObject,
	#instVars : [
		'agentExecution'
	],
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCFairyAgentProblem >> agentExecution [
	^ agentExecution
]

{ #category : #accessing }
BVCFairyAgentProblem >> agentExecution: anExecution [
	agentExecution := anExecution
]

{ #category : #accessing }
BVCFairyAgentProblem >> agentExecutionId [
	^ agentExecution ifNotNil: #executionId
]

{ #category : #magritte }
BVCFairyAgentProblem >> agentExecutionIdDescription [
	<magritteDescription>
	^ MAStringDescription new
		accessor: #agentExecutionId;
		comment: 'Inspect this execution in the parent chat object storage for the child messages and original error.';
		beOptional
]

{ #category : #views }
BVCFairyAgentProblem >> gtAgentExecutionFor: aView [
	<gtView>
	<gtLlmView>
	agentExecution ifNil: [ ^ aView empty ].
	^ aView forward
		title: 'Agent chat';
		priority: 10;
		object: [ agentExecution ];
		view: #gtViewAgentFor:
]
