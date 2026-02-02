Class {
	#name : 'CRMissingWorkerServiceException',
	#superclass : 'CRException',
	#instVars : [
		'worker',
		'serviceClass',
		'workUnitClass'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRMissingWorkerServiceException class >> worker: aWorker serviceClass: aServiceClass workUnitClass: aWorkUnitClass [
	^ self new
		worker: aWorker;
		serviceClass: aServiceClass;
		workUnitClass: aWorkUnitClass;
		yourself
]

{ #category : 'printing' }
CRMissingWorkerServiceException >> messageText [
	^ String
		streamContents: [ :s | 
			s
				nextPutAll: 'Missing worker service ';
				nextPutAll: serviceClass name;
				nextPutAll: ' required by ';
				nextPutAll: workUnitClass name;
				nextPutAll: ' on worker ';
				nextPutAll: worker displayName printString;
				nextPut: $. ]
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> serviceClass [
	^ serviceClass
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> serviceClass: anObject [
	serviceClass := anObject
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> workUnitClass [
	^ workUnitClass
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> workUnitClass: anObject [
	workUnitClass := anObject
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRMissingWorkerServiceException >> worker: anObject [
	worker := anObject
]
