Class {
	#name : 'CESimCollectEntitySnapshotsStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectEntitySnapshotsStageRunner >> runStage: aStage inContext: aContext [
	| engine subject partitionIds snapshots |
	engine := aContext engine.
	subject := aContext subject.

	partitionIds := subject partitionIdsForSnapshotCollection.

	snapshots := OrderedCollection new.
	partitionIds
		do: [ :partitionId | 
			| partition |
			partition := engine ensurePartition: partitionId.
			partition entities do: [ :entity | snapshots add: entity asSnapshot ] ].

	snapshots := (snapshots
			asSortedCollection: [ :a :b | (a at: #entityId) value < (b at: #entityId) value ])
			asOrderedCollection.

	self storeSnapshots: snapshots inContext: aContext
]

{ #category : 'running' }
CESimCollectEntitySnapshotsStageRunner >> storeSnapshots: snapshots inContext: aContext [
	self subclassResponsibility
]
