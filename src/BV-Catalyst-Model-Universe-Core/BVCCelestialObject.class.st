Class {
	#name : #BVCCelestialObject,
	#superclass : #BVCStoreObject,
	#instVars : [
		'identifier',
		'parent',
		'title',
		'comment',
		'seed'
	],
	#category : #'BV-Catalyst-Model-Universe-Core'
}

{ #category : #'instance creation' }
BVCCelestialObject class >> withParent: aCelestialObject [

  ^ self new
      parent: aCelestialObject;
      yourself
]

{ #category : #accessing }
BVCCelestialObject >> comment [
	^ comment
]

{ #category : #accessing }
BVCCelestialObject >> comment: anObject [
	comment := anObject
]

{ #category : #'as yet unclassified' }
BVCCelestialObject >> generateRandomSeed [

  | seedRange |
  seedRange := 1 << 32.
  ^ ( Random new next * seedRange ) asInteger
]

{ #category : #accessing }
BVCCelestialObject >> identifier [

  ^ identifier
]

{ #category : #initialization }
BVCCelestialObject >> initialize [
	super initialize.
	identifier := UUID new
]

{ #category : #accessing }
BVCCelestialObject >> parent [

  ^ parent
]

{ #category : #accessing }
BVCCelestialObject >> parent: anObject [

  parent := anObject
]

{ #category : #accessing }
BVCCelestialObject >> seed [

  ^ seed ifNil: [ seed := self generateRandomSeed ]
]

{ #category : #accessing }
BVCCelestialObject >> seed: anObject [

  seed := anObject
]

{ #category : #accessing }
BVCCelestialObject >> title [
	^ title
]

{ #category : #accessing }
BVCCelestialObject >> title: anObject [
	title := anObject
]
