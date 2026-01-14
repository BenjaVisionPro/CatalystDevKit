Class {
	#name : 'CESimCollectVisibleSnapshotsStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectVisibleSnapshotsStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| engine snapshots |
	engine := aCESimRunContext engine.
	snapshots := OrderedCollection new.

	engine regions
		do: [ :region | region notables do: [ :notable | snapshots add: notable asSnapshot ] ].	
	
	"Deterministic order: by entityId backing value."
	snapshots := (snapshots
			asSortedCollection: [ :a :b | (a at: #entityId) value < (b at: #entityId) value ])
			asOrderedCollection.

	aCESimRunContext stepCacheAt: #visibleSnapshots put: snapshots
]
