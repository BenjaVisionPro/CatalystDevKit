Class {
	#name : #BVCCelestialBody,
	#superclass : #BVCStoreObject,
	#instVars : [
		'title',
		'comment'
	],
	#category : #'BV-Catalyst-Model-Universe-Core'
}

{ #category : #accessing }
BVCCelestialBody >> comment [
	^ comment
]

{ #category : #accessing }
BVCCelestialBody >> comment: anObject [
	comment := anObject
]

{ #category : #accessing }
BVCCelestialBody >> title [
	^ title
]

{ #category : #accessing }
BVCCelestialBody >> title: anObject [
	title := anObject
]
