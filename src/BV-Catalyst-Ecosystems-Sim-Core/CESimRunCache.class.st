Class {
	#name : 'CESimRunCache',
	#superclass : 'CESimDictionary',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'capabilities - invocations' }
CESimRunCache >> addInvocation: aCESimCapabilityInvocation [
	self invocations add: aCESimCapabilityInvocation
]

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands [
	^ self at: #drainedCommands ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands: aCollection [
	self at: #drainedCommands put: aCollection
]

{ #category : 'capabilities - invocations' }
CESimRunCache >> invocations [
	^ self at: #invocations ifAbsentPut: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> localView [
	^ self at: #localView ifAbsent: [ nil ]
]

{ #category : 'accessing - api' }
CESimRunCache >> localView: aLocalView [
	self at: #localView put: aLocalView
]

{ #category : 'accessing - api' }
CESimRunCache >> postEntitySnapshots [
	^ self at: #postEntitySnapshots ifAbsent: [ #() ]
]

{ #category : 'accessing - api' }
CESimRunCache >> postEntitySnapshots: aCollection [
	self at: #postEntitySnapshots put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> preEntitySnapshots [
	^ self at: #preEntitySnapshots ifAbsent: [ #() ]
]

{ #category : 'accessing - api' }
CESimRunCache >> preEntitySnapshots: aCollection [
	self at: #preEntitySnapshots put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> result [
	^ self at: #result ifAbsent: [ nil ]
]

{ #category : 'accessing - api' }
CESimRunCache >> result: aCollection [
	self at: #result put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> tickEvents [
	^ self at: #tickEvents ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> tickEvents: aCollection [
	self at: #tickEvents put: aCollection
]
