Class {
	#name : #BVCDevKitWorld,
	#superclass : #GtWorld,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #accessing }
BVCDevKitWorld class >> defaultTitle [
	^ 'BenjaVision Catalyst DevKit'
]

{ #category : #initialization }
BVCDevKitWorld class >> initializeKnowledgeBase [
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

{ #category : #initialization }
BVCDevKitWorld >> defaultWorldElement [
	^ BVCDevKitWorldElement new
]

{ #category : #initialization }
BVCDevKitWorld >> initialize [
	super initialize.
	self markAsDefault.
	self updateWorldContent
]

{ #category : #initialization }
BVCDevKitWorld >> updateWorldContent [
	GtWorld allInstances
		do: [ :aGtWorld | aGtWorld root children first home updateWidget ]
]
