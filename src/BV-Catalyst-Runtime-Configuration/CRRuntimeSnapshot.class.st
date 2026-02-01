Class {
	#name : 'CRRuntimeSnapshot',
	#superclass : 'Object',
	#instVars : [
		'hostSnapshots',
		'workerSnapshots'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRRuntimeSnapshot >> hostSnapshots [ ^ hostSnapshots
]

{ #category : 'accessing' }
CRRuntimeSnapshot >> hostSnapshots: aCollection [ hostSnapshots := aCollection asOrderedCollection
]

{ #category : 'initialization' }
CRRuntimeSnapshot >> initialize [
	super initialize.
	hostSnapshots := OrderedCollection new.
	workerSnapshots := OrderedCollection new
]

{ #category : 'accessing' }
CRRuntimeSnapshot >> workerSnapshots [ ^ workerSnapshots
]

{ #category : 'accessing' }
CRRuntimeSnapshot >> workerSnapshots: aCollection [ workerSnapshots := aCollection asOrderedCollection
]
