"
I am the root of all objects that support storage in Catalyst:Store and transport via Catalyst:Connect
"
Class {
	#name : #BVCStoreObject,
	#superclass : #Object,
	#instVars : [
		'id'
	],
	#category : #'BV-Catalyst-Store-Core'
}

{ #category : #accessing }
BVCStoreObject >> id [
	^ id
]

{ #category : #accessing }
BVCStoreObject >> initialize [
	id := UUID new
]
