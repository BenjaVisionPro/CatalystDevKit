Class {
	#name : 'CRTestFailingWorkUnit',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'running' }
CRTestFailingWorkUnit >> executeWorkUnit [
	self error: 'Intentional test failure.'
]
