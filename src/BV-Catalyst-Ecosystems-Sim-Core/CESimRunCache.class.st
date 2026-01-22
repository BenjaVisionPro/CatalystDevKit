Class {
	#name : 'CESimRunCache',
	#superclass : 'CESimTempCache',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'capabilities - invocations' }
CESimRunCache >> addCapabilityInvocation: aCESimCapabilityInvocation [
	self capabilityInvocations add: aCESimCapabilityInvocation
]

{ #category : 'capabilities - invocations' }
CESimRunCache >> capabilityInvocations [
	^ self at: #capabilityInvocations ifAbsentPut: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands [
	^ self at: #drainedCommands ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands: aCollection [
	self at: #drainedCommands put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> perceivedVisibleSnapshots [
	^ self at: #perceivedVisibleSnapshots ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> perceivedVisibleSnapshots: aCollection [
	self at: #perceivedVisibleSnapshots put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> publishedVisibleSnapshots [
	^ self at: #publishedVisibleSnapshots ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> publishedVisibleSnapshots: aCollection [
	self at: #publishedVisibleSnapshots put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> result [
	^ self at: #result ifAbsent: [ nil ]
]

{ #category : 'accessing - api' }
CESimRunCache >> result: aCollection [
	self at: #result put: aCollection
]

{ #category : 'capabilities - invocations' }
CESimRunCache >> stimulusInvocations [
	^ self capabilityInvocations
		select: [ :each | each isKindOf: CESimStimulusInvocation ]
]

{ #category : 'accessing - api' }
CESimRunCache >> tickEvents [
	^ self at: #tickEvents ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> tickEvents: aCollection [
	self at: #tickEvents put: aCollection
]
