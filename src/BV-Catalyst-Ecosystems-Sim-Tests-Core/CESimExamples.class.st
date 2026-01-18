Class {
	#name : 'CESimExamples',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Ecosystems-Sim-Tests-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
}

{ #category : 'examples' }
CESimExamples >> example_createNotableCommandSpawnsInLocalViewSameTick [
	<gtExample>
	| engine region bubble pipeline stages view cmd |
	engine := CESimEngine new.	
	
	"Pipeline order: commands -> apply -> snapshots -> local view"
	stages := OrderedCollection new.
	stages
		add: (CESimStage new
				stageId: #consumeCommands;
				runner: CESimConsumeCommandsStageRunner new;
				yourself).
	stages
		add: (CESimStage new
				stageId: #applyUpdates;
				runner: CESimApplyUpdatesStageRunner new;
				yourself).
	stages
		add: (CESimStage new
				stageId: #collectVisible;
				runner: CESimCollectVisibleSnapshotsStageRunner new;
				yourself).
	stages
		add: (CESimStage new
				stageId: #buildLocalView;
				runner: CESimBuildLocalViewStageRunner new;
				yourself).

	pipeline := CESimPipeline new
			pipelineId: #bubble;
			stages: stages;
			yourself.
	engine bubblePipeline: pipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd := CESimCreateNotableCommand
			withDefinitionKey: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: cmd.

	view := engine advanceBubbleTickFor: bubble bubbleId.
	^ view
]

{ #category : 'examples' }
CESimExamples >> example_engineWithBubbleAndOneNotableApplied [
	<gtExample>
	| engine region bubble context notable update |
	engine := CESimEngine new.
	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.	
	
	"Construct (context factory) — no ids touched by caller."
	context := CESimRunContext
			for: bubble
			engine: engine
			tickId: engine currentTick
			environmentQuery: engine environmentQuery.

	notable := context
			newNotableWithDefinitionKey: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).	
	
	"Enqueue + apply (Ops are the authoritative change)."
	update := CESimUpdate new.
	update
		addEntityOp: (CESimAddNotableToRegionOp withRegionId: bubble homeRegionId notable: notable).
	context addUpdate: update.

	engine transactionRunner
		inTransactionDo: [ engine updateApplier applyUpdatesInContext: context ].

	^ Dictionary new
		at: #engine put: engine;
		at: #region put: region;
		at: #bubble put: bubble;
		at: #notable put: notable;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_engineWithCommandDrivenBubblePipeline [
	<gtExample>
	| engine pipeline stages |
	engine := CESimEngine new.

	stages := OrderedCollection new.
	stages
		add: (CESimStage new
			stageId: #consumeCommands;
			runner: CESimConsumeCommandsStageRunner new;
			yourself);
		add: (CESimStage new
			stageId: #collectVisibleSnapshots_pre;
			runner: CESimCollectVisibleSnapshotsStageRunner new;
			yourself);
		add: (CESimStage new
			stageId: #resolveIntent;
			runner: CESimResolveIntentStageRunner new;
			yourself);
		add: (CESimStage new
			stageId: #applyUpdates;
			runner: CESimApplyUpdatesStageRunner new;
			yourself);
		add: (CESimStage new
			stageId: #collectVisibleSnapshots_post;
			runner: CESimCollectVisibleSnapshotsStageRunner new;
			yourself);
		add: (CESimStage new
			stageId: #buildLocalView;
			runner: CESimBuildLocalViewStageRunner new;
			yourself).

	pipeline := CESimPipeline new.
	pipeline
		pipelineId: #bubble;
		stages: stages.

	engine bubblePipeline: pipeline.
	^ engine
]

{ #category : 'examples' }
CESimExamples >> example_localViewContainsEntityInteractionEventFromCommand [
	<gtExample>
	| engine region bubble createCmd view1 spawnedEntityId interactCmd view2 |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.	
	
	"Tick 1: create a notable so we have a real entityId to target."
	createCmd := CESimCreateNotableCommand
			withDefinitionKey: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	spawnedEntityId := view1 spawns first at: #entityId.	
	
	"Tick 2: interact with that entity."
	interactCmd := CESimInteractWithEntityCommand
			withTargetEntityId: spawnedEntityId
			type: #pet
			payload: (Dictionary new
					at: #hand put: #right;
					yourself).

	bubble enqueueCommand: interactCmd.
	view2 := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #entityId put: spawnedEntityId;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewContainsStimulusEmittedEventFromCommand [
	<gtExample>
	| engine region bubble cmd view |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd := CESimEmitStimulusAtTransformCommand
			type: #sound
			transform: (Dictionary new
					at: #pos put: #(5 0 0);
					yourself)
			intensity: 0.75.

	bubble enqueueCommand: cmd.

	view := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #view put: view;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsDeterministicSpawnOrderFromTwoCreateNotableCommands [
	<gtExample>
	| engine region bubble cmd1 cmd2 view |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd1 := CESimCreateNotableCommand
			withDefinitionKey: #demoNotableA
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	cmd2 := CESimCreateNotableCommand
			withDefinitionKey: #demoNotableB
			transform: (Dictionary new
					at: #pos put: #(1 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: cmd1.
	bubble enqueueCommand: cmd2.

	view := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #view put: view;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsSpawnForAppliedNotable [
	<gtExample>
	| seed engine bubble context collectRunner buildRunner view |
	seed := self example_engineWithBubbleAndOneNotableApplied.
	engine := seed at: #engine.
	bubble := seed at: #bubble.	
	
	"Fresh context for observation pass."
	context := CESimRunContext
			for: bubble
			engine: engine
			tickId: engine currentTick
			environmentQuery: engine environmentQuery.

	collectRunner := CESimCollectVisibleSnapshotsStageRunner new.
	buildRunner := CESimBuildLocalViewStageRunner new.

	collectRunner runStage: nil inContext: context.
	buildRunner runStage: nil inContext: context.

	view := context
			stepCacheAt: #result
			ifAbsent: [ self error: 'Expected #result in stepCache' ].

	^ Dictionary new
		at: #seed put: seed;
		at: #view put: view;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsSpawnFromCreateNotableCommandSameTick [
	<gtExample>
	| engine region bubble cmd view |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd := CESimCreateNotableCommand
			withDefinitionKey: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: cmd.

	view := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #engine put: engine;
		at: #region put: region;
		at: #bubble put: bubble;
		at: #view put: view;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsStateUpdateAfterEntityInteractionCommand [
	<gtExample>
	| engine region bubble createCmd view1 entityId interactCmd view2 |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.	
	
	"Tick 1: create a notable"
	createCmd := CESimCreateNotableCommand
			withDefinitionKey: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	entityId := view1 spawns first at: #entityId.	
	
	"Tick 2: interact -> should produce UPDATE with changed state"
	interactCmd := CESimInteractWithEntityCommand
			withTargetEntityId: entityId
			type: #pet
			payload: (Dictionary new
					at: #hand put: #right;
					yourself).

	bubble enqueueCommand: interactCmd.
	view2 := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #entityId put: entityId;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsStateUpdateAfterStimulusCommand [
	<gtExample>
	| engine region bubble createCmd view1 entityId stimulusCmd view2 |

	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	"Tick 1: create a notable"
	createCmd := CESimCreateNotableCommand
		withDefinitionKey: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	entityId := view1 spawns first at: #entityId.

	"Tick 2: emit stimulus -> should update the notable state"
	stimulusCmd := CESimEmitStimulusAtTransformCommand
		type: #sound
		transform: (Dictionary new at: #pos put: #(5 0 0); yourself)
		intensity: 0.75.

	bubble enqueueCommand: stimulusCmd.
	view2 := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #entityId put: entityId;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_localViewShowsUpdateAfterTransformChange [
	<gtExample>
	| seed engine bubble notable view1 context2 update2 collectRunner buildRunner view2 newTransform |
	seed := self example_localViewShowsSpawnForAppliedNotable.
	engine := (seed at: #seed) at: #engine.
	bubble := (seed at: #seed) at: #bubble.
	notable := (seed at: #seed) at: #notable.
	view1 := seed at: #view.

	newTransform := Dictionary new
			at: #pos put: #(10 0 0);
			yourself.

	context2 := CESimRunContext
			for: bubble
			engine: engine
			tickId: engine currentTick
			environmentQuery: engine environmentQuery.

	update2 := CESimUpdate new.
	update2
		addEntityOp: (CESimSetNotableTransformOp
				withRegionId: bubble homeRegionId
				entityId: notable entityId
				transform: newTransform).
	context2 addUpdate: update2.

	engine transactionRunner
		inTransactionDo: [ engine updateApplier applyUpdatesInContext: context2 ].

	collectRunner := CESimCollectVisibleSnapshotsStageRunner new.
	buildRunner := CESimBuildLocalViewStageRunner new.
	collectRunner runStage: nil inContext: context2.
	buildRunner runStage: nil inContext: context2.

	view2 := context2
			stepCacheAt: #result
			ifAbsent: [ self error: 'Expected #result in stepCache' ].

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #notable put: notable;
		at: #transform2 put: newTransform;
		yourself
]

{ #category : 'tests' }
CESimExamples >> test_createNotableCommandSpawnsInLocalViewSameTick [
	| view spawn |
	view := self example_createNotableCommandSpawnsInLocalViewSameTick.

	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #definitionKey) equals: #demoNotable.
	self assert: (spawn includesKey: #entityId)
]

{ #category : 'tests' }
CESimExamples >> test_localViewContainsEntityInteractionEventFromCommand [
	| result view2 entityId ev |
	result := self example_localViewContainsEntityInteractionEventFromCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	ev := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInteraction ]
			ifNone: [ self fail: 'Expected #creatureInteraction event in LocalView events' ].

	self assert: (ev at: #entityId) equals: entityId.
	self assert: (ev at: #interactionType) equals: #pet.
	self assert: ((ev at: #payload) at: #hand) equals: #right
]

{ #category : 'tests' }
CESimExamples >> test_localViewContainsStimulusEmittedEventFromCommand [
	| result view ev |
	result := self example_localViewContainsStimulusEmittedEventFromCommand.
	view := result at: #view.

	ev := view events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #stimulusEmitted ]
			ifNone: [ self fail: 'Expected #stimulusEmitted event in LocalView events' ].

	self assert: (ev at: #stimulusType) equals: #sound.
	self assert: (ev at: #intensity) equals: 0.75.
	self assert: ((ev at: #transform) at: #pos) equals: #(5 0 0)
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsDeterministicSpawnOrderFromTwoCreateNotableCommands [
	| result view spawns id1 id2 |
	result := self
			example_localViewShowsDeterministicSpawnOrderFromTwoCreateNotableCommands.
	view := result at: #view.
	spawns := view spawns.

	self assert: spawns size equals: 2.

	id1 := (spawns first at: #entityId) value.
	id2 := (spawns second at: #entityId) value.

	self assert: id1 < id2
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsSpawnForAppliedNotable [
	| result seed view notable spawn |
	result := self example_localViewShowsSpawnForAppliedNotable.
	seed := result at: #seed.
	view := result at: #view.
	notable := seed at: #notable.

	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #entityId) equals: notable entityId.
	self assert: (spawn at: #definitionKey) equals: #demoNotable
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsSpawnFromCreateNotableCommandSameTick [
	| result view spawn |
	result := self example_localViewShowsSpawnFromCreateNotableCommandSameTick.
	view := result at: #view.

	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #definitionKey) equals: #demoNotable.	"Audit facts still present (at least one commandAccepted event)."
	self
		assert: (view events
				anySatisfy: [ :e | (e at: #type ifAbsent: [ nil ]) = #commandAccepted ])
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsStateUpdateAfterEntityInteractionCommand [
	| result view2 entityId updateSnap state ev |
	result := self example_localViewShowsStateUpdateAfterEntityInteractionCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.
	self assert: view2 despawns isEmpty.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: entityId.

	state := updateSnap at: #state.
	self assert: (state at: #lastInteractionType) equals: #pet.
	self assert: ((state at: #lastInteractionPayload) at: #hand) equals: #right.

	ev := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInteraction ]
			ifNone: [ self fail: 'Expected #entityInteraction event' ].

	self assert: (ev at: #entityId) equals: entityId.
	self assert: (ev at: #interactionType) equals: #pet
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsStateUpdateAfterStimulusCommand [
	| result view2 entityId updateSnap state ev |
	result := self example_localViewShowsStateUpdateAfterStimulusCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.
	self assert: view2 despawns isEmpty.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: entityId.

	state := updateSnap at: #state.
	self assert: (state at: #lastStimulusType) equals: #sound.
	self assert: (state at: #lastStimulusIntensity) equals: 0.75.
	self assert: ((state at: #lastStimulusTransform) at: #pos) equals: #(5 0 0).

	ev := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #stimulusEmitted ]
			ifNone: [ self fail: 'Expected #stimulusEmitted event' ].

	self assert: (ev at: #stimulusType) equals: #sound.
	self assert: (ev at: #intensity) equals: 0.75.
	self assert: ((ev at: #transform) at: #pos) equals: #(5 0 0)
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsUpdateAfterTransformChange [
	| result view1 view2 notable updateSnap transform2 |
	result := self example_localViewShowsUpdateAfterTransformChange.
	view1 := result at: #view1.
	view2 := result at: #view2.
	notable := result at: #notable.
	transform2 := result at: #transform2.

	self assert: view1 spawns size equals: 1.
	self assert: view1 updates isEmpty.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.
	self assert: view2 despawns isEmpty.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: notable entityId.
	self assert: (updateSnap at: #transform) equals: transform2
]
