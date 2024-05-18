Class {
	#name : #BVCDevKitWorld,
	#superclass : #GtWorld,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #initialization }
BVCDevKitWorld >> defaultWorldElement [
	^ BVCDevKitWorldElement new
]

{ #category : #initialization }
BVCDevKitWorld >> initialize [
	super initialize.
	self markAsDefault.
	self initializeKnowledgeBase.
]

{ #category : #initialization }
BVCDevKitWorld >> initializeKnowledgeBase [
	IceRepository registry
		detect: [ :aRepository | aRepository name = 'CatalystDevKit' ]
		ifFound: [ :aRepository | 
			| defaultDatabase currentProperties |
			defaultDatabase := LeDatabasesRegistry defaultLogicalDatabase.
			currentProperties := defaultDatabase properties.
			currentProperties
				addRegisteredDirectory: aRepository repositoryDirectory / 'docs'.
			defaultDatabase reload ]
		ifNone: [ self inform: 'Repository not found.' ]
]
