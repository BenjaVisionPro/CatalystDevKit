Class {
	#name : 'CESimRunCache',
	#superclass : 'CESimTempCache',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands [
	^ self at: #drainedCommands ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> drainedCommands: aCollection [
	self at: #drainedCommands put: aCollection
]

{ #category : 'accessing - api' }
CESimRunCache >> result [
	^ self at: #result ifAbsent: [ OrderedCollection new ]
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

{ #category : 'accessing - api' }
CESimRunCache >> visibleSnapshots [
	^ self at: #visibleSnapshots ifAbsent: [ OrderedCollection new ]
]

{ #category : 'accessing - api' }
CESimRunCache >> visibleSnapshots: aCollection [
	self at: #visibleSnapshots put: aCollection
]
