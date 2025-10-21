Class {
	#name : #BVCAISession,
	#superclass : #Object,
	#instVars : [
		'id',
		'repoPath',
		'request',
		'branchName',
		'plan',
		'evidence',
		'buildHistory',
		'chatByRole'
	],
	#category : #'BV-Catalyst-Fairy-Core-AI'
}

{ #category : #'as yet unclassified' }
BVCAISession >> chatAt: aRole ifAbsentPut: aBlock [
  ^ chatByRole at: aRole ifAbsentPut: aBlock
]

{ #category : #'as yet unclassified' }
BVCAISession >> initialize [
  super initialize.
  chatByRole := Dictionary new
]
