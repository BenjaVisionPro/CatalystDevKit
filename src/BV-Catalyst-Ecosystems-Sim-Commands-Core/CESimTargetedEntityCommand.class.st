Class {
	#name : 'CESimTargetedEntityCommand',
	#superclass : 'CESimExternalCommand',
	#instVars : [
		'targetEntityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimTargetedEntityCommand class >> targetEntityId: aCEEntityId [
	^ self new
		targetEntityId: aCEEntityId;
		yourself
]

{ #category : 'targeting' }
CESimTargetedEntityCommand >> canTargetEntityId: anEntityId inContext: aSimContext update: aSimUpdate [
	"Answers true if this command can target anEntityId in the given run context.
	If false, emits a deterministic #targetRejected audit event into aSimUpdate and answers false."

	| decision allowed reason |
	decision := aSimContext targetingDecisionForEntityId: anEntityId.
	allowed := decision at: #allowed ifAbsent: [ false ].

	allowed ifTrue: [ ^ true ].

	reason := decision at: #reason ifAbsent: [ #rejected ].

	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #targetRejected;
				at: #commandType put: self class name asSymbol;
				at: #entityId put: anEntityId;
				at: #reason put: reason;
				at: #tickId put: aSimContext tickId;
				yourself).

	^ false
]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId [ ^ targetEntityId
]

{ #category : 'accessing' }
CESimTargetedEntityCommand >> targetEntityId: aCEEntityId [
	targetEntityId := aCEEntityId
]
