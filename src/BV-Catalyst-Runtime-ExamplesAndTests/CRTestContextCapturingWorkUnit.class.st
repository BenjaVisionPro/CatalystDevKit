Class {
	#name : 'CRTestContextCapturingWorkUnit',
	#superclass : 'CRWorkUnit',
	#instVars : [
		'capturedContext',
		'doneSemaphore'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'accessing' }
CRTestContextCapturingWorkUnit >> capturedContext [
	^ capturedContext
]

{ #category : 'accessing' }
CRTestContextCapturingWorkUnit >> doneSemaphore: anObject [
	doneSemaphore := anObject
]

{ #category : 'running' }
CRTestContextCapturingWorkUnit >> executeWorkUnitInContext: aContext [
	capturedContext := aContext.
	doneSemaphore ifNotNil: [ doneSemaphore signal ]
]
