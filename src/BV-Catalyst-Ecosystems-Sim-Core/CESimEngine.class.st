Class {
	#name : 'CESimEngine',
	#superclass : 'Object',
	#instVars : [
		'tickId',
		'bubblesById',
		'globalPipeline',
		'bubblePipeline',
		'environmentQuery',
		'runLog',
		'lastRunContext',
		'updateApplier',
		'transactionRunner',
		'idIssuer',
		'behaviour',
		'archetypes',
		'spawnSpecs',
		'partitionsById'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimEngine >> advanceGlobalTick [
	"Advance the global simulation by one tick.
     Runs the global pipeline for the selected regions (macro scheduling)."

	tickId := tickId + 1.

	globalPipeline ifNil: [ ^ self error: 'CESimEngine globalPipeline not set' ].

	self partitionsToAdvanceThisTick
		do: [ :region | self runGlobalPipelineOnPartition: region ].

	^ tickId
]

{ #category : 'running' }
CESimEngine >> advanceTickForBubbleId: aCEBubbleId [
	| bubble |
	"Advance one bubble. Returns a CESimLocalView (may be empty in v0)."
	bubblePipeline ifNil: [ ^ self error: 'CESimEngine bubblePipeline not set' ].

	bubble := bubblesById
			at: aCEBubbleId
			ifAbsent: [ ^ self error: 'Unknown bubbleId: ' , aCEBubbleId asString ].

	^ self runBubblePipelineOnBubble: bubble
]

{ #category : 'accessing' }
CESimEngine >> archetypes [
	^ archetypes
]

{ #category : 'accessing' }
CESimEngine >> behaviour [
	^ behaviour
]

{ #category : 'accessing' }
CESimEngine >> bubbleAt: aCEBubbleId ifAbsentPut: aBlock [
    ^ bubblesById at: aCEBubbleId ifAbsentPut: aBlock
]

{ #category : 'accessing' }
CESimEngine >> bubblePipeline [
    ^ bubblePipeline
]

{ #category : 'accessing' }
CESimEngine >> bubblePipeline: aPipeline [
    bubblePipeline := aPipeline
]

{ #category : 'accessing' }
CESimEngine >> bubbles [
    "Stable order (determinism): sort by bubbleId."
    ^ (bubblesById keys asSortedCollection)
        collect: [ :id | bubblesById at: id ]
]

{ #category : 'accessing' }
CESimEngine >> currentTick [
	^ tickId
]

{ #category : 'accessing' }
CESimEngine >> ensureBubble: aCEBubbleId [
	^ self
		bubbleAt: aCEBubbleId
		ifAbsentPut: [ CEBubbleAggregate withId: aCEBubbleId ]
]

{ #category : 'accessing' }
CESimEngine >> ensurePartition: aPartitionId [
	^ self
		partitionAt: aPartitionId
		ifAbsentPut: [ CESimPartition withId: aPartitionId ]
]

{ #category : 'accessing' }
CESimEngine >> environmentQuery [
    ^ environmentQuery
]

{ #category : 'accessing' }
CESimEngine >> environmentQuery: anEnvironmentQuery [
    environmentQuery := anEnvironmentQuery
]

{ #category : 'accessing' }
CESimEngine >> globalPipeline [
    ^ globalPipeline
]

{ #category : 'accessing' }
CESimEngine >> globalPipeline: aPipeline [
    globalPipeline := aPipeline
]

{ #category : 'testing' }
CESimEngine >> hasBubbleId: aCEBubbleId [
    ^ bubblesById includesKey: aCEBubbleId
]

{ #category : 'accessing' }
CESimEngine >> idIssuer [
	^ idIssuer
]

{ #category : 'initialization' }
CESimEngine >> initialize [
	super initialize.
	tickId := 0.
	partitionsById := Dictionary new.	"CERegionId -> region aggregate"
	bubblesById := Dictionary new.	"CEBubbleId -> bubble aggregate"
	runLog := OrderedCollection new.
	environmentQuery := CEFlatWorldEnvironment new.
	updateApplier := CESimUpdateApplier new.
	transactionRunner := CENullTransactionRunner new.
	idIssuer := CESequenceIdIssuer new.
	behaviour := CESimBehaviour new.
	archetypes := CESimEntityArchetypes new.
	spawnSpecs := CESimEntitySpawnSpecs new.
]

{ #category : 'accessing' }
CESimEngine >> lastRunContext [
	^ lastRunContext
]

{ #category : 'aggregates' }
CESimEngine >> newBubbleInPartitionId: aPartitionId [
    | bubbleId |
    bubbleId := idIssuer nextBubbleId.
    ^ self bubbleAt: bubbleId ifAbsentPut: [
        CEBubbleAggregate withId: bubbleId partitionId: aPartitionId
    ]
]

{ #category : 'aggregates' }
CESimEngine >> newPartition [
	| partitionId |
	partitionId := idIssuer nextRegionId.
	^ self
		partitionAt: partitionId
		ifAbsentPut: [ CESimPartition withId: partitionId ]
]

{ #category : 'accessing' }
CESimEngine >> partitionAt: aCERegionId ifAbsentPut: aBlock [
    ^ partitionsById at: aCERegionId ifAbsentPut: aBlock
]

{ #category : 'accessing' }
CESimEngine >> partitions [
    "Stable order (determinism): sort by regionId."
    ^ (partitionsById keys asSortedCollection)
        collect: [ :id | partitionsById at: id ]
]

{ #category : 'scheduling' }
CESimEngine >> partitionsToAdvanceThisTick [
	"Macro scheduling seam.
     Default behaviour: advance all regions in stable order.
     Later: return only active regions (hot/inbox/maintenance/wake zone)."

	^ self partitions
]

{ #category : 'private - running' }
CESimEngine >> runBubblePipelineOnBubble: aBubble [
    | context result |
    context := CESimRunContext
        for: aBubble
        engine: self
        tickId: tickId
        environmentQuery: environmentQuery.

    result := bubblePipeline runInContext: context.

    lastRunContext := context.
    ^ result
]

{ #category : 'private - running' }
CESimEngine >> runGlobalPipelineOnPartition: aPartition [
    | context |
    context := CESimRunContext
        for: aPartition
        engine: self
        tickId: tickId
        environmentQuery: environmentQuery.

    globalPipeline runInContext: context.

    lastRunContext := context
]

{ #category : 'accessing' }
CESimEngine >> spawnSpecs [
	^ spawnSpecs
]

{ #category : 'accessing' }
CESimEngine >> transactionRunner [
	^ transactionRunner
]

{ #category : 'accessing' }
CESimEngine >> updateApplier [
	^ updateApplier
]
