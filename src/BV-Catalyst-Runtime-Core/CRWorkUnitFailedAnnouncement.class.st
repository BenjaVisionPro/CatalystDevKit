Class {
	#name : 'CRWorkUnitFailedAnnouncement',
	#superclass : 'CRWorkerAnnouncement',
	#instVars : [
		'exception',
		'workUnit'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkUnitFailedAnnouncement class >> worker: aWorker workUnit: aWorkUnit exception: anException [
	^ (self worker: aWorker)
		workUnit: aWorkUnit;
		exception: anException;
		yourself
]

{ #category : 'accessing' }
CRWorkUnitFailedAnnouncement >> exception [
	^ exception
]

{ #category : 'accessing' }
CRWorkUnitFailedAnnouncement >> exception: anObject [
	exception := anObject
]

{ #category : 'accessing' }
CRWorkUnitFailedAnnouncement >> workUnit [
	^ workUnit
]

{ #category : 'accessing' }
CRWorkUnitFailedAnnouncement >> workUnit: anObject [
	workUnit := anObject
]
