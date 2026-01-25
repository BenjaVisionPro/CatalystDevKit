Class {
	#name : 'CESimEffectBehaviourModule',
	#superclass : 'CESimBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'private - perception' }
CESimEffectBehaviourModule >> perceivedVisibleEntityIdsInContext: aCESimRunContext [
	^ (self perceivedVisibleSnapshotsInContext: aCESimRunContext)
		collect: [ :snap | snap at: #entityId ]
]

{ #category : 'private - perception' }
CESimEffectBehaviourModule >> perceivedVisibleSnapshotsInContext: aCESimRunContext [
	^ aCESimRunContext runCache perceivedSnapshots ifNil: [ #() ]
]
