Class {
	#name : 'CRWorkerNotAcceptingWorkException',
	#superclass : 'Exception',
	#instVars : [
		'worker',
		'reason',
		'workUnit'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkerNotAcceptingWorkException class >> worker: aWorker workUnit: aUnit reason: aString [
	^ self new
		worker: aWorker
		workUnit: aUnit
		reason: aString
]

{ #category : 'printing' }
CRWorkerNotAcceptingWorkException >> messageText [
	^ String
		streamContents: [ :s | 
			s nextPutAll: 'Worker not accepting work'.
			reason
				ifNotNil: [ s
						nextPutAll: ' (';
						nextPutAll: reason;
						nextPut: $) ] ]
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> reason [
	^ reason
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> reason: anObject [
	reason := anObject
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> workUnit [
	^ workUnit
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> workUnit: anObject [
	workUnit := anObject
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> worker: anObject [
	worker := anObject
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> worker: aWorker workUnit: aUnit reason: aString [
	worker := aWorker.
	workUnit := aUnit.
	reason := aString
]
