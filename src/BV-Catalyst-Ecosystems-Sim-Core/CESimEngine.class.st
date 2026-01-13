Class {
	#name : 'CESimEngine',
	#superclass : 'Object',
	#instVars : [
		'tickId',
		'regionsById',
		'bubblesById',
		'globalPipeline',
		'bubblePipeline',
		'environmentQuery',
		'runLog'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimEngine >> advanceBubbleTickFor: aCEBubbleId [
	| bubble |
	"Advance one bubble. Returns a CESimLocalView (may be empty in v0)."
	bubblePipeline ifNil: [ ^ self error: 'CESimEngine bubblePipeline not set' ].

	bubble := bubblesById
			at: aCEBubbleId
			ifAbsent: [ ^ self error: 'Unknown bubbleId: ' , aCEBubbleId asString ].

	^ self runBubblePipelineOnBubble: bubble
]

{ #category : 'running' }
CESimEngine >> advanceGlobalTick [
	"Advance the global simulation by one tick.
     Runs the global pipeline once per region in stable order."

	tickId := tickId + 1.

	globalPipeline ifNil: [ ^ self error: 'CESimEngine globalPipeline not set' ].

	self regions do: [ :region | self runGlobalPipelineOnRegion: region ].

	^ tickId
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

{ #category : 'testing' }
CESimEngine >> hasRegionId: aCERegionId [
    ^ regionsById includesKey: aCERegionId
]

{ #category : 'initialization' }
CESimEngine >> initialize [
    super initialize.
    tickId := 0.
    regionsById := Dictionary new.  "CERegionId -> region aggregate"
    bubblesById := Dictionary new.  "CEBubbleId -> bubble aggregate"
    runLog := OrderedCollection new.
    environmentQuery := CEFlatWorldEnvironment new.
    "globalPipeline and bubblePipeline will be installed explicitly."
]

{ #category : 'accessing' }
CESimEngine >> regionAt: aCERegionId ifAbsentPut: aBlock [
    ^ regionsById at: aCERegionId ifAbsentPut: aBlock
]

{ #category : 'accessing' }
CESimEngine >> regions [
    "Stable order (determinism): sort by regionId."
    ^ (regionsById keys asSortedCollection)
        collect: [ :id | regionsById at: id ]
]

{ #category : 'private - running' }
CESimEngine >> runBubblePipelineOnBubble: aBubble [
    | context |
    context := CESimRunContext
        for: aBubble
        engine: self
        tickId: tickId
        environmentQuery: environmentQuery.

    ^ bubblePipeline runInContext: context
]

{ #category : 'private - running' }
CESimEngine >> runGlobalPipelineOnRegion: aRegion [
    | context |
    context := CESimRunContext
        for: aRegion
        engine: self
        tickId: tickId
        environmentQuery: environmentQuery.

    globalPipeline runInContext: context
]
