Class {
	#name : 'CRWorkQueue',
	#superclass : 'Object',
	#instVars : [
		'sharedQueue'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'queue' }
CRWorkQueue >> enqueue: aWorkItem [
	"I enqueue a work item."

	sharedQueue nextPut: aWorkItem.
	^ aWorkItem
]

{ #category : 'initialization' }
CRWorkQueue >> initialize [
	"I initialise my queue."

	super initialize.
	sharedQueue := SharedQueue new
]

{ #category : 'queue' }
CRWorkQueue >> next [
	"Ianswer the next work item, waiting until one exists."

	^ sharedQueue next
]

{ #category : 'queue' }
CRWorkQueue >> nextOrNil [
	"I answer the next work item if one is available, otherwise nil."

	^ sharedQueue nextOrNil
]
