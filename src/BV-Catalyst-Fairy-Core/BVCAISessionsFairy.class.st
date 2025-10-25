Class {
	#name : #BVCAISessionsFairy,
	#superclass : #BVCAIFariesModel,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCAISessionsFairy >> coderForClass: aClass [
	^ self coders
		detect: [ :each | each theClass = aClass ]
		ifNone: [ | coder |
			items add: aClass.
			coder := self newCoderFor: aClass.
			coders add: coder.
			coder ]
]

{ #category : #updating }
BVCAISessionsFairy >> forPackage: aPackage [
	items := aPackage definedClasses
		asSortedCollection: [ :a :b | a name < b name ].
	self updateCoders
]

{ #category : #updating }
BVCAISessionsFairy >> forPackageTag: aPackageTag [
	items := aPackageTag classes
		asSortedCollection: [ :a :b | a name < b name ].
	self updateCoders
]

{ #category : #private }
BVCAISessionsFairy >> newCoderFor: aClass [
	| coder |
	coder := GtPharoBehaviorCoder forClass: aClass.
	^ coder
]
