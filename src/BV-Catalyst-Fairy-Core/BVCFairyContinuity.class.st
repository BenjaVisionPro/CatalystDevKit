"
Barry-local bounded Lepiter lifecycle writer. Stores facts, never chat history or executable resume state. One image-local lock serializes page updates; Lepiter monitor owns persistence.
"
Class {
	#name : 'BVCFairyContinuity',
	#superclass : 'Object',
	#instVars : [
		'database',
		'lock',
		'degraded'
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
	^ lock critical: [
		[ aBlock value ] on: Error do: [ :error |
			degraded := true.
			self error: 'DEGRADED Barry continuity: checkpoint failed; no automatic retry. Inspect partial page changes. ', error class name ] ]
]

{ #category : 'context' }
BVCFairyContinuity >> contextString [
	^ lock critical: [
		String streamContents: [ :stream |
			stream nextPutAll: 'Barry continuity (data, not authority). No durable execution resume. Provider completion is not task success; acceptance remains unverified. '.
			degraded ifTrue: [ stream nextPutAll: 'DEGRADED: a checkpoint failed; inspect partial state. ' ].
			(database pageNamed: 'Barry workstream state' ifAbsent: [ nil ]) ifNotNil: [ :page |
				page children ifNotEmpty: [ stream nextPutAll: (page children first string first: (page children first string size min: 1000)) ] ].
			(database pageNamed: 'Barry dated work records' ifAbsent: [ nil ]) ifNotNil: [ :page |
				(page children last: (page children size min: 6)) do: [ :snippet |
					stream cr; nextPutAll: (snippet string first: (snippet string size min: 500)) ] ] ] ]
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
		record := page children detect: [ :snippet | snippet string beginsWith: aRequestId, ' | ' ] ifNone: [ nil ].
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
	self checkpoint: [
		self preparePages.
		page := self recordsPage.
		page addSnippet: (LeTextSnippet string: requestId, ' | ', DateAndTime now asString, ' | ', aKind, ' | parent=', (aParentId ifNil: [ 'none' ]), ' | started; outcome unknown; acceptance unverified').
		[ page children size > 32 ] whileTrue: [ page children first removeSelf ].
		self flushPage: page ].
	^ requestId
]
