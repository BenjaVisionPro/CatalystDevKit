Class {
	#name : 'CRRuntimeWorkerAnnouncement',
	#superclass : 'CRRuntimeAnnouncement',
	#instVars : [
		'worker'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRRuntimeWorkerAnnouncement class >> runtime: aRuntime worker: aWorker [
	^ (super runtime: aRuntime)
		worker: aWorker;
		yourself
]

{ #category : 'accessing' }
CRRuntimeWorkerAnnouncement >> worker [
	^ worker
]

{ #category : 'accessing' }
CRRuntimeWorkerAnnouncement >> worker: anObject [
	worker := anObject
]
