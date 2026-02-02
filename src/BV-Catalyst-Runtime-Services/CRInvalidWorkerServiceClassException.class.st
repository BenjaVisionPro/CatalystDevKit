Class {
	#name : 'CRInvalidWorkerServiceClassException',
	#superclass : 'CRException',
	#instVars : [
		'worker',
		'given'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRInvalidWorkerServiceClassException class >> worker: aWorker given: anObject [
	^ self new
		worker: aWorker;
		given: anObject;
		yourself
]

{ #category : 'accessing' }
CRInvalidWorkerServiceClassException >> given [
	^ given
]

{ #category : 'accessing' }
CRInvalidWorkerServiceClassException >> given: anObject [
	given := anObject
]

{ #category : 'printing' }
CRInvalidWorkerServiceClassException >> messageText [
	^ String
		streamContents: [ :s | 
			s
				nextPutAll: 'Worker service class must be a Class. Got ';
				nextPutAll: given printString;
				nextPutAll: ' on worker ';
				nextPutAll: worker displayName printString;
				nextPut: $. ]
]

{ #category : 'accessing' }
CRInvalidWorkerServiceClassException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRInvalidWorkerServiceClassException >> worker: anObject [
	worker := anObject
]
