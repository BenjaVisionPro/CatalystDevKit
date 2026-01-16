Class {
	#name : 'CESimCollectVisibleSnapshotsStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectVisibleSnapshotsStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| engine bubble snapshots |
	engine := aCESimRunContext engine.
	bubble := aCESimRunContext subject.
	snapshots := OrderedCollection new.

	bubble relevantRegionIds
		do: [ :regionId | 
			(engine ensureRegion: regionId) notables
				do: [ :notable | snapshots add: notable asSnapshot ] ].	
				
	"Deterministic order: by entityId backing value."
	snapshots := (snapshots
			asSortedCollection: [ :a :b | (a at: #entityId) value < (b at: #entityId) value ])
			asOrderedCollection.

	aCESimRunContext stepCacheAt: #visibleSnapshots put: snapshots
]
