Class {
	#name : 'CESimCollectPublishedVisibleSnapshotsStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectPublishedVisibleSnapshotsStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| engine subject regionIds snapshots |
	engine := aCESimRunContext engine.
	subject := aCESimRunContext subject.

	"Select which regions to scan.
     - Bubble: use #relevantRegionIds (v0: { homeRegionId }).
     - Region: scan that region only.
     Determinism: snapshots must be stably ordered by entityId backing value."
	regionIds := (subject respondsTo: #relevantRegionIds)
		ifTrue: [ subject relevantRegionIds ]
		ifFalse: [ (subject respondsTo: #aggregateId)
			ifTrue: [ { subject aggregateId } ]
			ifFalse: [ #() ] ].

	snapshots := OrderedCollection new.
	regionIds do: [ :regionId |
		| region |
		region := engine ensureRegion: regionId.
		region notables do: [ :notable | snapshots add: notable asSnapshot ]
	].

	"Deterministic order: by entityId backing value."
	snapshots := (snapshots
			asSortedCollection: [ :a :b | (a at: #entityId) value < (b at: #entityId) value ])
			asOrderedCollection.

	aCESimRunContext runCache publishedVisibleSnapshots: snapshots
]
