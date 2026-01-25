Class {
	#name : 'CESimCollectPostEntitySnapshotsStageRunner',
	#superclass : 'CESimCollectEntitySnapshotsStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimCollectPostEntitySnapshotsStageRunner >> storeSnapshots: snapshots inContext: aContext [
	aContext runCache postEntitySnapshots: snapshots
]
