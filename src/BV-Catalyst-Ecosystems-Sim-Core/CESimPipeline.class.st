Class {
	#name : 'CESimPipeline',
	#superclass : 'Object',
	#instVars : [
		'pipelineId',
		'stages'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'initialization' }
CESimPipeline >> initialize [
    super initialize.
    stages := OrderedCollection new
]

{ #category : 'accessing' }
CESimPipeline >> pipelineId [
	^ pipelineId
]

{ #category : 'accessing' }
CESimPipeline >> pipelineId: anObject [
	pipelineId := anObject
]

{ #category : 'running' }
CESimPipeline >> runInContext: aCESimRunContext [
    stages do: [ :stage |
        (stage shouldRunInContext: aCESimRunContext) ifTrue: [
            stage runInContext: aCESimRunContext
        ] ].
    ^ aCESimRunContext
]

{ #category : 'accessing' }
CESimPipeline >> stages [
	^ stages
]

{ #category : 'accessing' }
CESimPipeline >> stages: anObject [
	stages := anObject
]
