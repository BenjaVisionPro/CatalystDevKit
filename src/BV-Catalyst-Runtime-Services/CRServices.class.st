Class {
	#name : 'CRServices',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'byClass'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRServices class >> onWorker: aCRWorker [
	^ self new
		initializeOnWorker: aCRWorker;
		yourself
]

{ #category : 'initialization' }
CRServices >> initializeOnWorker: aCRWorker [
	worker := aCRWorker.
	byClass := Dictionary new
]

{ #category : 'accessing' }
CRServices >> worker [
	^ worker
]
