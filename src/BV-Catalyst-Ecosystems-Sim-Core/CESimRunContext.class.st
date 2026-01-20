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

{ #category : 'targeting' }
CESimRunContext >> gateTargetEntityId: anEntityId forCommand: aCommand module: aModuleSymbol intoUpdate: aCESimUpdate [
	"Evaluates targetability and emits a deterministic rejection audit event if disallowed.
	Returns true if allowed, false otherwise."

	| decision allowed reason |

	decision := self targetingDecisionForEntityId: anEntityId.
	allowed := decision at: #allowed ifAbsent: [ false ].

	allowed ifTrue: [ ^ true ].

	reason := decision at: #reason ifAbsent: [ #rejected ].

	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #targetRejected;
		at: #module put: aModuleSymbol;
		at: #commandType put: aCommand class name asSymbol;
		at: #entityId put: anEntityId;
		at: #reason put: reason;
		at: #tickId put: self tickId;
		yourself).

	^ false
]

{ #category : 'step cache' }
CESimRunContext >> hasStepCacheKey: aKey [
	"Legacy alias. Prefer #runCache includesKey:."
	^ runCache includesKey: aKey
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

{ #category : 'step cache' }
CESimRunContext >> stepCache [
	"Legacy alias."
	^ runCache
]

{ #category : 'step cache' }
CESimRunContext >> stepCacheAt: aKey ifAbsent: aBlock [
	"Legacy alias."
	^ self runCacheAt: aKey ifAbsent: aBlock
]

{ #category : 'step cache' }
CESimRunContext >> stepCacheAt: aKey put: aValue [
	"Legacy alias."
	self runCacheAt: aKey put: aValue
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
