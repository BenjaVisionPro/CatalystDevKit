Class {
	#name : 'CESimCollectPreEntitySnapshotsStageRunner',
	#superclass : 'CESimCollectEntitySnapshotsStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectPreEntitySnapshotsStageRunner >> storeSnapshots: snapshots inContext: aContext [
	aContext runCache preEntitySnapshots: snapshots
]
