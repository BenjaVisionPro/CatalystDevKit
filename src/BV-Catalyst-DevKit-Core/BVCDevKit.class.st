Class {
	#name : #BVCDevKit,
	#superclass : #Object,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #accessing }
BVCDevKit class >> iceRepository [
	^ IceRepository registry
		detect: [ :aRepository | aRepository name = self repoName ]
]

{ #category : #accessing }
BVCDevKit class >> initializeKnowledgeBase [
	self iceRepository
		ifNotNil: [ :aRepository | 
			| defaultDatabase currentProperties |
			defaultDatabase := LeDatabasesRegistry defaultLogicalDatabase.
			currentProperties := defaultDatabase properties.
			currentProperties
				addRegisteredDirectory: aRepository repositoryDirectory / 'docs'.
			defaultDatabase reload ]
]

{ #category : #accessing }
BVCDevKit class >> installDirectory [
	^ self iceRepository
		ifNil: [ self error: 'No repository found' ]
		ifNotNil: [ :aRepository | aRepository repositoryDirectory ]
]

{ #category : #accessing }
BVCDevKit class >> repoName [
	^ 'CatalystDevKit'
]
