Class {
	#name : 'CRDuplicateWorkerServiceException',
	#superclass : 'CRException',
	#instVars : [
		'worker',
		'serviceClass'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRDuplicateWorkerServiceException class >> worker: aWorker serviceClass: aServiceClass [
	^ self new
		worker: aWorker;
		serviceClass: aServiceClass;
		yourself
]

{ #category : 'printing' }
CRDuplicateWorkerServiceException >> messageText [
	^ String
		streamContents: [ :s | 
			s
				nextPutAll: 'Duplicate worker service installation ';
				nextPutAll: serviceClass name;
				nextPutAll: ' on worker ';
				nextPutAll: worker displayName printString;
				nextPut: $. ]
]

{ #category : 'accessing' }
CRDuplicateWorkerServiceException >> serviceClass [
	^ serviceClass
]

{ #category : 'accessing' }
CRDuplicateWorkerServiceException >> serviceClass: anObject [
	serviceClass := anObject
]

{ #category : 'accessing' }
CRDuplicateWorkerServiceException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRDuplicateWorkerServiceException >> worker: anObject [
	worker := anObject
]
