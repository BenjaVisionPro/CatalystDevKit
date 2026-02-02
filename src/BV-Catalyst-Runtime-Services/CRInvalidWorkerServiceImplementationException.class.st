Class {
	#name : 'CRInvalidWorkerServiceImplementationException',
	#superclass : 'CRException',
	#instVars : [
		'worker',
		'serviceClass'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRInvalidWorkerServiceImplementationException class >> worker: aWorker serviceClass: aServiceClass [
	^ self new
		worker: aWorker;
		serviceClass: aServiceClass;
		yourself
]

{ #category : 'printing' }
CRInvalidWorkerServiceImplementationException >> messageText [
	^ String
		streamContents: [ :s | 
			s
				nextPutAll: 'Worker service ';
				nextPutAll: serviceClass name;
				nextPutAll: ' must inherit from CRWorkerService on worker ';
				nextPutAll: worker displayName printString;
				nextPut: $. ]
]

{ #category : 'accessing' }
CRInvalidWorkerServiceImplementationException >> serviceClass [
	^ serviceClass
]

{ #category : 'accessing' }
CRInvalidWorkerServiceImplementationException >> serviceClass: anObject [
	serviceClass := anObject
]

{ #category : 'accessing' }
CRInvalidWorkerServiceImplementationException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRInvalidWorkerServiceImplementationException >> worker: anObject [
	worker := anObject
]
