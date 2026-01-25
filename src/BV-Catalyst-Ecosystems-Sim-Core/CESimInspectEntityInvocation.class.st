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
CESimInspectEntityInvocation >> contributeIntoUpdate: aUpdate inContext: aContext [
	| decision snapshot |
	decision := aContext
			canTargetEntityId: targetEntityId
			invocation: self
			update: aUpdate.

	(decision at: #allowed) ifFalse: [ ^ self ].

	snapshot := aContext perceivedSnapshotForEntityId: targetEntityId.

	aUpdate
		addEvent: (Dictionary new
				at: #type put: #entityInspected;
				at: #entityId put: targetEntityId;
				at: #snapshot put: snapshot;
				at: #tickId put: aContext tickId;
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
