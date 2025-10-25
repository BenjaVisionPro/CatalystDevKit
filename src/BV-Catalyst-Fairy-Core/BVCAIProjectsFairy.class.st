Class {
	#name : #BVCAIProjectsFairy,
	#superclass : #BVCAIFariesModel,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #comparing }
BVCAIProjectsFairy >> = anObject [
	^ self class = anObject class
]

{ #category : #ui }
BVCAIProjectsFairy >> asCoderViewModel [
	^ GtPharoPackagesCoderViewModel new projectsFairyModel: self
]

{ #category : #accessing }
BVCAIProjectsFairy >> fairyForProject: aProject [
	^ self faries
		detect: [ :each | each project = aProject ]
		ifNone: [ | fairy |
			items add: aProject.
			fairy := self newFairyFor: aProject.
			faries add: fairy.
			fairy ]
]

{ #category : #accessing }
BVCAIProjectsFairy >> fairyForSession: aSession [
	^ (self fairyForProject: aSession project)
		ifNotNil: [ :fairy | fairy fairyForSession: aSession ]
]

{ #category : #comparing }
BVCAIProjectsFairy >> hash [
	^ self class hash
]

{ #category : #accessing }
BVCAIProjectsFairy >> icon [
	^ BrGlamorousVectorIcons packageicon asElement
]

{ #category : #accessing }
BVCAIProjectsFairy >> name [
	^ 'Project'
]

{ #category : #private }
BVCAIProjectsFairy >> newFairyFor: aProject [
	^ BVCAIProjectsFairy forProject: aProject
]
