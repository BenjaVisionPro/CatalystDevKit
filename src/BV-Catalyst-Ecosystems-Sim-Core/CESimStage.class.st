Class {
	#name : 'CESimStage',
	#superclass : 'Object',
	#instVars : [
		'stageId',
		'schedule',
		'runner'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'printing' }
CESimStage >> printOn: aStream [
	aStream
		nextPutAll: self class name asString;
		nextPut: $(;
		nextPutAll: stageId asString;
		nextPut: $)
]

{ #category : 'running' }
CESimStage >> runInContext: aCESimRunContext [
	runner
		ifNil: [ ^ self error: 'Stage runner not set for stage: ' , stageId asString ].
	^ runner runStage: self inContext: aCESimRunContext
]

{ #category : 'accessing' }
CESimStage >> runner [
	^ runner
]

{ #category : 'accessing' }
CESimStage >> runner: anObject [
	runner := anObject
]

{ #category : 'accessing' }
CESimStage >> schedule [
	^ schedule
]

{ #category : 'accessing' }
CESimStage >> schedule: anObject [
	schedule := anObject
]

{ #category : 'running' }
CESimStage >> shouldRunInContext: aCESimRunContext [
    "v0: if no schedule, always run. Schedule can become a strategy object later."
    schedule ifNil: [ ^ true ].
    ^ schedule shouldRunStage: self inContext: aCESimRunContext
]

{ #category : 'accessing' }
CESimStage >> stageId [
	^ stageId
]

{ #category : 'accessing' }
CESimStage >> stageId: anObject [
	stageId := anObject
]
