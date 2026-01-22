Class {
	#name : 'CESimRunContext',
	#superclass : 'Object',
	#instVars : [
		'engine',
		'tickId',
		'environmentQuery',
		'subject',
		'updates',
		'runCache'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimRunContext class >> for: aSubject engine: anEngine tickId: aTickId environmentQuery: anEnvironmentQuery [
	^ self new
		engine: anEngine;
		tickId: aTickId;
		environmentQuery: anEnvironmentQuery;
		subject: aSubject;
		yourself
]

{ #category : 'updates' }
CESimRunContext >> addUpdate: aCESimUpdate [
	updates add: aCESimUpdate
]

{ #category : 'convenience' }
CESimRunContext >> bubble [
	^ subject
]

{ #category : 'targeting' }
CESimRunContext >> canTargetEntityId: anEntityId [
	"Central targeting seam.
	 Default (strict): entity must be in this tick's perceived snapshots.
	 If environmentQuery provides a targeting policy, delegate to it."

	| perceivedSnapshots bubble env |
	bubble := self subject.
	perceivedSnapshots := self runCache perceivedVisibleSnapshots ifNil: [ #() ].
	env := self environmentQuery.

	(env notNil and: [ env respondsTo: #canTargetEntityId:forBubble:perceivedSnapshots: ])
		ifTrue: [ ^ env canTargetEntityId: anEntityId forBubble: bubble perceivedSnapshots: perceivedSnapshots ].

	^ perceivedSnapshots anySatisfy: [ :snap | (snap at: #entityId) = anEntityId ]
]

{ #category : 'run cache' }
CESimRunContext >> clearRunCache [
	runCache removeAll
]

{ #category : 'step cache' }
CESimRunContext >> clearStepCache [
	"Legacy alias. Prefer #clearRunCache."
	self clearRunCache
]

{ #category : 'updates' }
CESimRunContext >> clearUpdates [
	updates removeAll
]

{ #category : 'accessing' }
CESimRunContext >> engine [
	^ engine
]

{ #category : 'accessing' }
CESimRunContext >> engine: anObject [
	engine := anObject
]

{ #category : 'accessing' }
CESimRunContext >> environmentQuery [
	^ environmentQuery
]

{ #category : 'accessing' }
CESimRunContext >> environmentQuery: anObject [
	environmentQuery := anObject
]

{ #category : 'step cache' }
CESimRunContext >> hasStepCacheKey: aKey [
	"Legacy alias. Prefer #runCache includesKey:."
	^ runCache includesKey: aKey
]

{ #category : 'convenience' }
CESimRunContext >> homeRegionId [
	^ subject homeRegionId
]

{ #category : 'initialization' }
CESimRunContext >> initialize [
	super initialize.
	updates := OrderedCollection new.
	runCache := CESimRunCache new
]

{ #category : 'factory - entities' }
CESimRunContext >> newNotableWithDefinitionKey: aKey transform: aTransform state: aState [
	"Canonical creation path for Notables.
	 Callers never mint ids; context/engine owns determinism + id issuance."

	^ CENotable new
		definitionKey: aKey;
		transform: aTransform;
		state: aState;
		entityId: self engine idIssuer nextEntityId;
		yourself	"or whatever your issuer selector is"
]

{ #category : 'printing' }
CESimRunContext >> printOn: aStream [
	aStream
		nextPutAll: self class name asString;
		nextPutAll: '(tick=';
		nextPutAll: tickId asString;
		nextPutAll: ', subject=';
		print: subject;
		nextPut: $)
]

{ #category : 'convenience' }
CESimRunContext >> region [
	^ engine ensureRegion: self homeRegionId
]

{ #category : 'run cache' }
CESimRunContext >> runCache [
	^ runCache
]

{ #category : 'run cache' }
CESimRunContext >> runCacheAt: aKey ifAbsent: aBlock [
	^ runCache at: aKey ifAbsent: aBlock
]

{ #category : 'run cache' }
CESimRunContext >> runCacheAt: aKey put: aValue [
	runCache at: aKey put: aValue
]

{ #category : 'accessing' }
CESimRunContext >> subject [
	^ subject
]

{ #category : 'accessing' }
CESimRunContext >> subject: anObject [
	subject := anObject
]

{ #category : 'targeting' }
CESimRunContext >> targetingDecisionForEntityId: anEntityId [
	"Returns a Dictionary with at least:
	 #allowed -> Boolean
	 #reason  -> Symbol (when not allowed)
	Default policy: must be perceived this tick.
	Delegates to environmentQuery if it provides a richer policy."

	| perceivedSnapshots bubble env |

	perceivedSnapshots := self runCache perceivedVisibleSnapshots ifNil: [ #() ].
	bubble := self subject.
	env := self environmentQuery.

	(env notNil and: [ env respondsTo: #targetingDecisionForEntityId:forBubble:perceivedSnapshots: ])
		ifTrue: [ ^ env targetingDecisionForEntityId: anEntityId forBubble: bubble perceivedSnapshots: perceivedSnapshots ].

	^ (perceivedSnapshots anySatisfy: [ :snap | (snap at: #entityId) = anEntityId ])
		ifTrue: [ Dictionary new at: #allowed put: true; yourself ]
		ifFalse: [ Dictionary new at: #allowed put: false; at: #reason put: #notPerceived; yourself ]

]

{ #category : 'accessing' }
CESimRunContext >> tickId [
	^ tickId
]

{ #category : 'accessing' }
CESimRunContext >> tickId: anObject [
	tickId := anObject
]

{ #category : 'updates' }
CESimRunContext >> updates [
	^ updates copy
]
