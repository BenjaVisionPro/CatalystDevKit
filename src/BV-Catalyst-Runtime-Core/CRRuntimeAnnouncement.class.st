Class {
	#name : 'CRRuntimeAnnouncement',
	#superclass : 'CRAnnouncement',
	#instVars : [
		'runtime'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRRuntimeAnnouncement class >> runtime: aRuntime [
	^ self new
		runtime: aRuntime;
		yourself
]

{ #category : 'accessing' }
CRRuntimeAnnouncement >> runtime [
	^ runtime
]

{ #category : 'accessing' }
CRRuntimeAnnouncement >> runtime: anObject [
	runtime := anObject
]
