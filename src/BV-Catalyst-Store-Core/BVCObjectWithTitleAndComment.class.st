Class {
	#name : #BVCObjectWithTitleAndComment,
	#superclass : #BVCStoreObject,
	#instVars : [
		'title',
		'comment'
	],
	#category : #'BV-Catalyst-Store-Core'
}

{ #category : #accessing }
BVCObjectWithTitleAndComment >> comment [
	^ comment
]

{ #category : #accessing }
BVCObjectWithTitleAndComment >> comment: anObject [
	comment := anObject
]

{ #category : #accessing }
BVCObjectWithTitleAndComment >> title [
	^ title
]

{ #category : #accessing }
BVCObjectWithTitleAndComment >> title: anObject [
	title := anObject
]
