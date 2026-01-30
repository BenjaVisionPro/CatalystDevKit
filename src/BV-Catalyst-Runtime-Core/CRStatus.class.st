Class {
	#name : 'CRStatus',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'statuses' }
CRStatus class >> all [
	^ {self stopped.
		self startingUp.
		self running.
		self shuttingDown.
		self degraded.
		self error}
]

{ #category : 'statuses' }
CRStatus class >> degraded [
	^ #degraded
]

{ #category : 'statuses' }
CRStatus class >> error [
	^ #error
]

{ #category : 'statuses' }
CRStatus class >> running [
	^ #running
]

{ #category : 'statuses' }
CRStatus class >> shuttingDown [
	^ #shuttingDown
]

{ #category : 'statuses' }
CRStatus class >> startingUp [
	^ #startingUp
]

{ #category : 'statuses' }
CRStatus class >> stopped [
	^ #stopped
]
