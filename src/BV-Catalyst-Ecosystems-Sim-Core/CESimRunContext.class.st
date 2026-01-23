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

{ #category : 'as yet unclassified' }
CESimRunContext >> canTargetEntityId: anEntityId invocation: anInvocation update: aSimUpdate [
	"Answers true if target is allowed for this invocation’s targeting profile.
	If false, emits deterministic #targetRejected event into the update and answers false."

	| decision allowed reason |
	decision := self
			targetingDecisionForEntityId: anEntityId
			profile: anInvocation targetingProfile.
	allowed := decision at: #allowed ifAbsent: [ false ].
	allowed ifTrue: [ ^ true ].

	reason := decision at: #reason ifAbsent: [ CESimDecisionOutcome notPresent ].

	aSimUpdate
		addEvent: (Dictionary new
				at: #type put: #targetRejected;
				at: #entityId put: anEntityId;
				at: #reason put: reason;
				at: #tickId put: self tickId;
				yourself).

	^ false
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
CESimRunContext >> newEntityWithDefinitionKey: aKey transform: aTransform state: aState [
	"Canonical creation path for Notables.
	 Callers never mint ids; context/engine owns determinism + id issuance."

	^ CECreatureEntity new
		definitionKey: aKey;
		transform: aTransform;
		state: aState;
		entityId: self engine idIssuer nextEntityId;
		yourself	"or whatever your issuer selector is"
]

{ #category : 'targeting' }
CESimRunContext >> ownerDecision [
	| ownerId |
	ownerId := self subject ownerEntityId.
	ownerId
		ifNil: [ ^ Dictionary new
				at: #allowed put: false;
				at: #reason put: CESimDecisionOutcome notPresent;
				yourself ].

	^ Dictionary new
		at: #allowed put: true;
		at: #entityId put: ownerId;
		yourself
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
CESimRunContext >> targetingDecisionForEntityId: anEntityId profile: aProfile [
	| rules rejection |
	rules := self engine behaviour targetingPolicies
			at: aProfile
			ifAbsent: [ ^ Dictionary new
					at: #allowed put: false;
					at: #reason put: CESimDecisionOutcome noPolicy;
					yourself ].

	rules
		do: [ :rule | 
			rejection := rule rejectionReasonForTargetEntityId: anEntityId inContext: self.
			rejection
				ifNotNil: [ ^ Dictionary new
						at: #allowed put: false;
						at: #reason put: rejection;
						yourself ] ].

	^ Dictionary new
		at: #allowed put: true;
		yourself
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
