Class {
	#name : 'CESimSetFocusEntityInvocation',
	#superclass : 'CESimFocusInvocation',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimSetFocusEntityInvocation class >> targetEntityId: aCEEntityId [
	^ self new
		targetEntityId: aCEEntityId;
		yourself
]

{ #category : 'contributing' }
CESimSetFocusEntityInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	(aSimContext canTargetEntityId: targetEntityId invocation: self update: aSimUpdate)
		ifFalse: [ ^ self ].

	"Outcome event for now. (Later: authoritative focus op / state.)"
	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #focusSet;
				at: #entityId put: targetEntityId;
				at: #tickId put: aSimContext tickId;
				yourself)
]

{ #category : 'targeting' }
CESimSetFocusEntityInvocation >> targetingProfile [
	^ CESimTargetingProfile focus
]

{ #category : 'accessing' }
CESimSetFocusEntityInvocation >> targetEntityId [
	^ targetEntityId
]

{ #category : 'accessing' }
CESimSetFocusEntityInvocation >> targetEntityId: anObject [
	targetEntityId := anObject
]
