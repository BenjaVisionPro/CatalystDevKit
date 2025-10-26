Class {
	#name : #BVCAISessionsFairy,
	#superclass : #BVCAIFariesModel,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCAISessionsFairy >> fairyForSession: aSession [
	^ self coders
		detect: [ :each | each theClass = aSession ]
		ifNone: [ | fairy |
			items add: aSession.
			fairy := self newFairyFor: aSession.
			faries add: fairy.
			fairy ]
]

{ #category : #updating }
BVCAISessionsFairy >> forProject: aProject [
	items := aProject sessions asSortedCollection: [ :a :b | a name < b name ].
	self updateFaries
]

{ #category : #private }
BVCAISessionsFairy >> newCoderFor: aClass [
	| coder |
	coder := GtPharoBehaviorCoder forClass: aClass.
	^ coder
]

{ #category : #private }
BVCAISessionsFairy >> newFairyFor: aSession [
	| fairy |
	fairy := GtPharoBehaviorCoder forSession: aSession.
	^ fairy
]
