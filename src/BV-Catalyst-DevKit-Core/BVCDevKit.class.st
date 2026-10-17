Class {
	#name : 'BVCDevKit',
	#superclass : 'Object',
	#category : 'BV-Catalyst-DevKit-Core',
	#package : 'BV-Catalyst-DevKit-Core'
}

{ #category : 'accessing' }
BVCDevKit class >> iceRepository [
	^ IceRepository registry
		detect: [ :aRepository | aRepository name = self repoName ]
]

{ #category : 'accessing' }
BVCDevKit class >> initializeKnowledgeBase [
	^ BaselineOfCatalystDevKit loadLepiter
]

{ #category : 'accessing' }
BVCDevKit class >> installDirectory [
	^ self iceRepository
		ifNil: [ self error: 'No repository found' ]
		ifNotNil: [ :aRepository | aRepository repositoryDirectory ]
]

{ #category : 'accessing' }
BVCDevKit class >> repoName [
	^ 'CatalystDevKit'
]
