Class {
	#name : 'CESimInspectEntityInvocation',
	#superclass : 'CESimInteractionInvocation',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInspectEntityInvocation class >> targetEntityId: aCEEntityId [
	^ self new
		targetEntityId: aCEEntityId;
		yourself
]

{ #category : 'as yet unclassified' }
CESimInspectEntityInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| decision allowed reason snapshots snapshot |
	decision := aSimContext targetingDecisionForEntityId: targetEntityId.
	allowed := decision at: #allowed ifAbsent: [ false ].

	allowed
		ifFalse: [ reason := decision at: #reason ifAbsent: [ #rejected ].
			aSimUpdate
				addEvent: (Dictionary new
						at: #type put: #targetRejected;
						at: #entityId put: targetEntityId;
						at: #reason put: reason;
						at: #tickId put: aSimContext tickId;
						yourself).
			^ self ].

	snapshots := aSimContext runCache perceivedVisibleSnapshots ifNil: [ #() ].
	snapshot := snapshots
			detect: [ :snap | (snap at: #entityId) = targetEntityId ]
			ifNone: [ Dictionary new
					at: #entityId put: targetEntityId;
					yourself ].

	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #entityInspected;
				at: #entityId put: targetEntityId;
				at: #snapshot put: snapshot;
				at: #tickId put: aSimContext tickId;
				yourself)
]

{ #category : 'accessing' }
CESimInspectEntityInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]
