"
Isolated roots for gate examples only; production builder always includes registered Barry chats.
"
Class {
	#name : 'BVCFairyAgentBuilderStub',
	#superclass : 'BVCFairyAgentBuilder',
	#instVars : [
		'roots'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'validation' }
BVCFairyAgentBuilderStub >> mutationOwnershipRootsFor: aParent [
	^ roots ifNil: [ { aParent } ]
]

{ #category : 'accessing' }
BVCFairyAgentBuilderStub >> roots: aCollection [
	roots := aCollection
]
