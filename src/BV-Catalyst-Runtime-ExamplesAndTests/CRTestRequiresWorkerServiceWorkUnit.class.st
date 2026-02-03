Class {
	#name : 'CRTestRequiresWorkerServiceWorkUnit',
	#superclass : 'CRWorkUnit',
	#instVars : [
		'doneSemaphore',
		'observedService',
		'observedWorker',
		'observedServices'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'service context' }
CRTestRequiresWorkerServiceWorkUnit class >> requiredWorkerServiceClass [
	^ CRTestWorkerService
]

{ #category : 'accessing' }
CRTestRequiresWorkerServiceWorkUnit >> doneSemaphore: anObject [
	doneSemaphore := anObject
]

{ #category : 'running' }
CRTestRequiresWorkerServiceWorkUnit >> executeWorkUnitInContext: aContext [
	observedWorker := aContext worker.
	observedServices := aContext services.
	observedService := aContext service.
	doneSemaphore ifNotNil: [ doneSemaphore signal ]
]

{ #category : 'accessing' }
CRTestRequiresWorkerServiceWorkUnit >> observedService [
	^ observedService
]

{ #category : 'accessing' }
CRTestRequiresWorkerServiceWorkUnit >> observedServices [
	^ observedServices
]

{ #category : 'accessing' }
CRTestRequiresWorkerServiceWorkUnit >> observedWorker [
	^ observedWorker
]
