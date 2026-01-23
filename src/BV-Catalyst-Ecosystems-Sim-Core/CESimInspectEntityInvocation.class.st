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
	| snapshots snapshot |

	(aSimContext canTargetEntityId: targetEntityId invocation: self update: aSimUpdate)
		ifFalse: [ ^ self ].

	snapshots := aSimContext runCache perceivedVisibleSnapshots.
	snapshot := snapshots
		detect: [ :snap | (snap at: #entityId) = targetEntityId ]
		ifNone: [ Dictionary new
			at: #entityId put: targetEntityId;
			yourself ].

	aSimUpdate addEvent: (Dictionary new
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

{ #category : 'targeting' }
CESimInspectEntityInvocation >> targetingProfile [
	^ CESimTargetingProfile inspect
]
