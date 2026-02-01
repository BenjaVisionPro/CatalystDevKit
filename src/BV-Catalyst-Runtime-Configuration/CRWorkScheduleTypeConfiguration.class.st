Class {
	#name : 'CRWorkScheduleTypeConfiguration',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'validation' }
CRWorkScheduleTypeConfiguration >> validateOn: aValidationResult forScheduleIdentifier: aScheduleIdentifier workerIdentifier: aWorkerIdentifier [
	self subclassResponsibility
]
