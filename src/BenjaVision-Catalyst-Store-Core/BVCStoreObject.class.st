Class {
	#name : #BVCStoreObject,
	#superclass : #Object,
	#instVars : [
		'id'
	],
	#category : #'BenjaVision-Catalyst-Store-Core'
}

{ #category : #accessing }
BVCStoreObject >> id [
	^ id
]

{ #category : #accessing }
BVCStoreObject >> initialize [
	id := UUID new
]
