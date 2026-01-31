Class {
	#name : 'CRAnnouncementChannel',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'channels' }
CRAnnouncementChannel class >> all [
	^ {self operations.
		self telemetry.
		self debug.
		self security.
		self audit}
]

{ #category : 'channels' }
CRAnnouncementChannel class >> audit [
	^ #auditChannel
]

{ #category : 'channels' }
CRAnnouncementChannel class >> debug [
	^ #debugChannel
]

{ #category : 'channels' }
CRAnnouncementChannel class >> operations [
	^ #operationsChannel
]

{ #category : 'channels' }
CRAnnouncementChannel class >> security [
	^ #securityChannel
]

{ #category : 'channels' }
CRAnnouncementChannel class >> telemetry [
	^ #telemetryChannel
]
