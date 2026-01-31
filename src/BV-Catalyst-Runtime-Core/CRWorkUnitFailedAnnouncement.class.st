Class {
	#name : 'CRWorkUnitFailedAnnouncement',
	#superclass : 'CRWorkerAnnouncement',
	#instVars : [
		'unit',
		'exception'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRWorkUnitFailedAnnouncement class >> worker: aWorker unit: aWorkUnit exception: anException [
	^ (self worker: aWorker)
		unit: aWorkUnit;
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
CRWorkUnitFailedAnnouncement >> unit [
	^ unit
]

{ #category : 'accessing' }
CRWorkUnitFailedAnnouncement >> unit: anObject [
	unit := anObject
]
