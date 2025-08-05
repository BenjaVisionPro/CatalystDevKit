Class {
	#name : #BVCHost,
	#superclass : #Object,
	#instVars : [
		'hostname',
		'key',
		'servers'
	],
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #accessing }
BVCHost >> hostname [

  ^ hostname
]

{ #category : #accessing }
BVCHost >> hostname: anObject [

  hostname := anObject
]

{ #category : #'as yet unclassified' }
BVCHost >> initialize [
	super initialize.
	servers := Dictionary new.
]
