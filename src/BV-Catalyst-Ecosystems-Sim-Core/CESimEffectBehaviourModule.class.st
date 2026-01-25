Class {
	#name : 'CESimEffectBehaviourModule',
	#superclass : 'CESimBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'private - perception' }
CESimEffectBehaviourModule >> preEntityIdsInContext: aCESimRunContext [
	^ (self preEntitySnapshotsInContext: aCESimRunContext)
		collect: [ :snap | snap at: #entityId ]
]

{ #category : 'private - perception' }
CESimEffectBehaviourModule >> preEntitySnapshotsInContext: aCESimRunContext [
	^ aCESimRunContext runCache preEntitySnapshots ifNil: [ #() ]
]
