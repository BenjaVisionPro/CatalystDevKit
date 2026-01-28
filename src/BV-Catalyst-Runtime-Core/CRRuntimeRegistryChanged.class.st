Class {
	#name : 'CRRuntimeRegistryChanged',
	#superclass : 'Announcement',
	#instVars : [
		'runtime'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRRuntimeRegistryChanged class >> runtime: aRuntime [
	"I create an announcement that the runtime registry changed involving aRuntime."

	^ self new
		runtime: aRuntime;
		yourself
]

{ #category : 'accessing' }
CRRuntimeRegistryChanged >> runtime [
	"I answer the runtime involved in the change."

	^ runtime
]

{ #category : 'accessing' }
CRRuntimeRegistryChanged >> runtime: aRuntime [
	"I set the runtime involved in the change."

	runtime := aRuntime
]
