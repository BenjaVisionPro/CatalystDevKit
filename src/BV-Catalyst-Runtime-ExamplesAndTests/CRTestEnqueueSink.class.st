Class {
	#name : 'CRTestEnqueueSink',
	#superclass : 'Object',
	#instVars : [
		'items'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'queue' }
CRTestEnqueueSink >> enqueueScheduled: aWorkUnit scheduleKey: aKey boundaryMillis: aBoundaryMillis [
	"Record the scheduling call exactly as the scheduler sees it."

	items
		add: {aWorkUnit.
				aKey.
				aBoundaryMillis}
]

{ #category : 'initialization' }
CRTestEnqueueSink >> initialize [
	super initialize.
	items := OrderedCollection new
]

{ #category : 'accessing' }
CRTestEnqueueSink >> items [
	^ items
]

{ #category : 'accessing' }
CRTestEnqueueSink >> size [
	^ items size
]
