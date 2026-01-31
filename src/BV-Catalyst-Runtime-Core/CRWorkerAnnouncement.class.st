Class {
	#name : 'CRWorkerAnnouncement',
	#superclass : 'CRAnnouncement',
	#instVars : [
		'worker'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkerAnnouncement class >> worker: aWorker [
	^ self
		worker: aWorker;
		yourself
]

{ #category : 'accessing' }
CRWorkerAnnouncement >> worker [
	^ worker
]

{ #category : 'accessing' }
CRWorkerAnnouncement >> worker: anObject [
	worker := anObject
]
