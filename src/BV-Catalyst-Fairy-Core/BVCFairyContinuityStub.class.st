"
Controlled volatile continuity writer; no disk persistence claim.
"
Class {
	#name : 'BVCFairyContinuityStub',
	#superclass : 'BVCFairyContinuity',
	#instVars : [
		'failWrites'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'accessing' }
BVCFairyContinuityStub >> failWrites: aBoolean [
	failWrites := aBoolean
]

{ #category : 'persistence' }
BVCFairyContinuityStub >> flushPage: aPage [
	failWrites = true ifTrue: [ self error: 'Controlled persistence failure' ]
]
