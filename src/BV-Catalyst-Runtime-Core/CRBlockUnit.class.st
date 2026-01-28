Class {
	#name : 'CRBlockUnit',
	#superclass : 'CRWorkUnit',
	#instVars : [
		'block'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRBlockUnit class >> on: aBlock [
	"I answer a work item that runs the block."

	^ self new
		block: aBlock;
		yourself
]

{ #category : 'accessing' }
CRBlockUnit >> block: anObject [
	block := anObject
]

{ #category : 'accessing' }
CRBlockUnit >> run [
	"I run my block."

	block value
]
