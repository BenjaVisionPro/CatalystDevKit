Class {
	#name : 'CRWorkerNotAcceptingWorkException',
	#superclass : 'Exception',
	#instVars : [
		'worker',
		'unit',
		'reason'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkerNotAcceptingWorkException class >> worker: aWorker unit: aUnit reason: aString [
	^ self new
		worker: aWorker
		unit: aUnit
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
CRWorkerNotAcceptingWorkException >> unit [
	^ unit
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerNotAcceptingWorkException >> worker: aWorker unit: aUnit reason: aString [
	worker := aWorker.
	unit := aUnit.
	reason := aString
]
