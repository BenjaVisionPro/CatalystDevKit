Class {
	#name : 'CRTestFailingWorkUnit',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'running' }
CRTestFailingWorkUnit >> executeWorkUnitInContext: aCRWorkUnitExecutionContext [
	self error: 'Intentional test failure.'
]
