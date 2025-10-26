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
BVCAIProjectsFairy >> asFairyViewModel [
	^ GtPharoPackagesCoderViewModel new projectsFairyModel: self
]

{ #category : #ui }
BVCAIProjectsFairy >> asNewFairyModelWithSameSubject [
	"Return new fairy model with same subject (e.g., project, session)"

	<return: #BVCAIFairyModel>
	^ self class forItems: items
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
	^ GtPharoPackageCoder forProject: aProject
]
