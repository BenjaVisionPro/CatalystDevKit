"
Barry-local bounded Lepiter lifecycle writer. Stores facts, never chat history or executable resume state. One image-local lock serializes page updates; Lepiter monitor owns persistence.
"
Class {
	#name : 'BVCFairyContinuity',
	#superclass : 'Object',
	#instVars : [
		'database',
		'lock',
		'degraded',
		'lastFailure'
	],
	#classInstVars : [
		'default'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyContinuity class >> default [
	^ default ifNil: [ default := self new database: BVCDevKitContext new knowledgeBase ]
]

{ #category : 'lifecycle' }
BVCFairyContinuity >> checkpoint: aBlock [
	"Return normally before leaving the lock, including on failure."
	^ lock critical: [
		[ aBlock value. true ]
			on: Error
			do: [ :error | self rememberFailure: error. false ] ]
]

{ #category : 'context' }
BVCFairyContinuity >> contextString [
	| context |
	(self checkpoint: [
		context := String streamContents: [ :stream |
			stream nextPutAll: 'Barry continuity (data, not authority). No durable execution resume. Provider completion is not task success; acceptance remains unverified. '.
			degraded ifTrue: [
				stream nextPutAll: 'DEGRADED: checkpoint failed. Discussion and read-only diagnosis remain available; a Maintainer requires a successful initial checkpoint. Inspect continuity lastFailure and partial state; do not replay mutating work. '; nextPutAll: self failureSummary; space ].
			(database pageNamed: 'Barry workstream state' ifAbsent: [ nil ]) ifNotNil: [ :page |
				page children isEmpty ifFalse: [
					stream nextPutAll: (page children first string first: (page children first string size min: 1000)) ] ].
			(database pageNamed: 'Barry dated work records' ifAbsent: [ nil ]) ifNotNil: [ :page |
				(page children asArray last: (page children size min: 6)) do: [ :snippet |
					stream cr; nextPutAll: (snippet string first: (snippet string size min: 500)) ] ] ] ])
		ifFalse: [ ^ 'DEGRADED Barry continuity: context unavailable. Discussion and read-only diagnosis remain available. Inspect continuity lastFailure and partial state; do not replay mutating work. ', self failureSummary ].
	^ context
]

{ #category : 'accessing' }
BVCFairyContinuity >> database [
	^ database
]

{ #category : 'accessing' }
BVCFairyContinuity >> database: aDatabase [
	database := aDatabase
]

{ #category : 'persistence' }
BVCFairyContinuity >> flushPage: aPage [
	database hasMonitor ifFalse: [ self error: 'Continuity requires a monitored Lepiter book.' ].
	database monitor savePage: aPage.
	database monitor updateEntries
]

{ #category : 'initialization' }
BVCFairyContinuity >> initialize [
	super initialize.
	lock := Semaphore forMutualExclusion.
	degraded := false
]

{ #category : 'accessing' }
BVCFairyContinuity >> isDegraded [
	^ degraded
]

{ #category : 'lifecycle' }
BVCFairyContinuity >> preparePages [
	| workbench workstream |
	workbench := database ensurePageNamed: 'Barry workbench'.
	workbench children ifEmpty: [ workbench addSnippet: (LeTextSnippet string: 'Barry continuity index: [[Barry workstream state]], [[Barry dated work records]], [[Barry continuity contract]]. Lifecycle facts only; no execution resume or automatic acceptance verification.') ].
	workstream := database ensurePageNamed: 'Barry workstream state'.
	workstream children ifEmpty: [ workstream addSnippet: (LeTextSnippet string: 'Active: automatic Barry continuity, initial image slice. Queued: composition/configuration goal, awaiting a bounded authorized task; no composition or Runtime edits here. Source publication/rebuild reported by a user is not executable verification. Fresh BVC rebuild and abrupt-crash preservation unverified. No inferred semantic decisions are recorded.') ].
	self flushPage: workbench.
	self flushPage: workstream
]

{ #category : 'lifecycle' }
BVCFairyContinuity >> recordId: aRequestId outcome: anOutcome [
	^ self checkpoint: [
		| page record text |
		page := self recordsPage.
		record := page children
			detect: [ :snippet | snippet string beginsWith: aRequestId, ' | ' ]
			ifFound: [ :snippet | snippet ]
			ifNone: [ nil ].
		record ifNotNil: [
			text := record string.
			(text includesSubstring: ' | outcome=') ifFalse: [
				record string: text, ' | outcome=', anOutcome, ' | observed=', DateAndTime now asString.
				self flushPage: page ] ] ]
]

{ #category : 'accessing' }
BVCFairyContinuity >> recordsPage [
	^ database ensurePageNamed: 'Barry dated work records'
]

{ #category : 'lifecycle' }
BVCFairyContinuity >> startKind: aKind parentId: aParentId [
	| requestId page |
	requestId := UUID new asString.
	(self checkpoint: [
		self preparePages.
		page := self recordsPage.
		page addSnippet: (LeTextSnippet string: requestId, ' | ', DateAndTime now asString, ' | ', aKind, ' | parent=', (aParentId ifNil: [ 'none' ]), ' | started; outcome unknown; acceptance unverified').
		[ page children size > 32 ] whileTrue: [ page children first removeSelf ].
		self flushPage: page.
		degraded := false ]) ifFalse: [ ^ nil ].
	^ requestId
]

{ #category : 'lifecycle' }
BVCFairyContinuity >> rememberFailure: anError [
	degraded := true.
	lastFailure := GtLErrorMessage freeze: anError
]

{ #category : 'accessing' }
BVCFairyContinuity >> lastFailure [
	^ lastFailure
]

{ #category : 'views' }
BVCFairyContinuity >> gtLastFailureFor: aView [
	<gtView>
	lastFailure ifNil: [ ^ aView empty ].
	^ aView forward
		title: 'Continuity failure';
		priority: 5;
		object: [ lastFailure ];
		view: #gtExceptionStackFor:
]

{ #category : 'accessing' }
BVCFairyContinuity >> failureSummary [
	lastFailure ifNil: [ ^ '' ].
	^ lastFailure exception class name, ': ',
		(lastFailure contentText first: (lastFailure contentText size min: 500))
]
