Class {
	#name : 'CESimExamples',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Ecosystems-Sim-Tests-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
}

{ #category : 'examples' }
CESimExamples >> example_createNotableCommandProducesAuditEventAndSpawn [
	<gtExample>
	| engine region bubble cmd view |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: cmd.
	view := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #view put: view;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_createNotableCommandSpawnsInLocalViewSameTick [
	<gtExample>
	| engine region bubble cmd view |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	cmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
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
		newEntityWithDefinitionKey: #demoNotable
		transform: (Dictionary new
			at: #pos put: #(0 0 0);
			yourself)
		state: (Dictionary new
			at: #mood put: #chill;
			yourself).

	"Enqueue + apply (Ops are the authoritative change)."
	update := CESimUpdate new.
	update addEntityOp: (CESimAddOp
		withRegionId: bubble homeRegionId
		entity: notable).
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
				stageId: #collectPerception;
				runner: CESimCollectPerceivedVisibleSnapshotsStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #modules;
				runner: CESimModulesStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #applyUpdates;
				runner: CESimApplyUpdatesStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #collectPublication;
				runner: CESimCollectPublishedVisibleSnapshotsStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #buildLocalView;
				runner: CESimBuildLocalViewStageRunner new;
				yourself).

	pipeline := CESimPipeline new
			pipelineId: #bubble;
			stages: stages;
			yourself.

	engine bubblePipeline: pipeline.
	self seedArchetypesAndSpawnSpecsOn: engine.
	^ engine
]

{ #category : 'examples' }
CESimExamples >> example_localViewContainsEntityInspectedEventFromCommand [
	<gtExample>
	| engine region bubble createCmd view1 entityId inspectCmd view2 |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	"Tick 1: create a notable to inspect."
	createCmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.
	entityId := view1 spawns first at: #entityId.

	"Tick 2: inspect it."
	inspectCmd := CESimInspectEntityCommand targetEntityId: entityId.
	bubble enqueueCommand: inspectCmd.
	view2 := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #view2 put: view2;
		at: #entityId put: entityId;
		yourself

]

{ #category : 'examples' }
CESimExamples >> example_localViewContainsEntityInteractionEventFromCommand [
	<gtExample>
	| engine region bubble createCmd view1 spawnedEntityId interactCmd view2 |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	"Tick 1: create a notable so we have a real entityId to target."
	createCmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	spawnedEntityId := view1 spawns first at: #entityId.

	"Tick 2: interact with that entity."
	interactCmd := CESimInteractWithEntityCommand
		withTargetEntityId: spawnedEntityId
		type: #pet
		payload: (Dictionary new at: #hand put: #right; yourself).

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
		transform: (Dictionary new at: #pos put: #(5 0 0); yourself)
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

	cmd1 := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	cmd2 := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(1 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

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

	"Fresh context for publication pass (LocalView is built from published snapshots)."
	context := CESimRunContext
		for: bubble
		engine: engine
		tickId: engine currentTick
		environmentQuery: engine environmentQuery.

	collectRunner := CESimCollectPublishedVisibleSnapshotsStageRunner new.
	buildRunner := CESimBuildLocalViewStageRunner new.

	collectRunner runStage: nil inContext: context.
	buildRunner runStage: nil inContext: context.

	view := context runCache result.

	^ Dictionary new
		at: #seed put: seed;
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
	createCmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	entityId := view1 spawns first at: #entityId.

	"Tick 2: interact -> should produce UPDATE (semantic state changed)"
	interactCmd := CESimInteractWithEntityCommand
		withTargetEntityId: entityId
		type: #pet
		payload: (Dictionary new at: #hand put: #right; yourself).

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
	createCmd := CESimAddEntityCommand
		withSpawnSpecId: #demoNotable
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #mood put: #chill; yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	entityId := view1 spawns first at: #entityId.

	"Tick 2: emit stimulus -> should update the notable semantic state"
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
		addEntityOp: (CESimSetTransformOp
				withRegionId: bubble homeRegionId
				entityId: notable entityId
				transform: newTransform).
	context2 addUpdate: update2.

	engine transactionRunner
		inTransactionDo: [ engine updateApplier applyUpdatesInContext: context2 ].

	collectRunner := CESimCollectPublishedVisibleSnapshotsStageRunner new.
	buildRunner := CESimBuildLocalViewStageRunner new.
	collectRunner runStage: nil inContext: context2.
	buildRunner runStage: nil inContext: context2.

	view2 := context2 runCache result.

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #notable put: notable;
		at: #transform2 put: newTransform;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_removeNotableCommandDespawnsInLocalViewSameTick [
	<gtExample>
	| engine region bubble createCmd view1 entityId removeCmd view2 |
	engine := self example_engineWithCommandDrivenBubblePipeline.

	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	createCmd := CESimAddEntityCommand
			withSpawnSpecId: #demoNotable
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			state: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: createCmd.
	view1 := engine advanceBubbleTickFor: bubble bubbleId.

	entityId := view1 spawns first at: #entityId.

	removeCmd := CESimRemoveEntityCommand targetEntityId: entityId.
	bubble enqueueCommand: removeCmd.
	view2 := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #view1 put: view1;
		at: #view2 put: view2;
		at: #entityId put: entityId;
		yourself
]

{ #category : 'examples' }
CESimExamples >> example_stimulusOnlyAffectsVisibleNotables [
	<gtExample>
	| engine regionA regionB bubble context notableA notableB stateA0 stateB0 update view |

	engine := self example_engineWithCommandDrivenBubblePipeline.

	regionA := engine newRegion.
	regionB := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: regionA aggregateId.

	"Context factory (no ids touched by caller)."
	context := CESimRunContext
		for: bubble
		engine: engine
		tickId: engine currentTick
		environmentQuery: engine environmentQuery.

	notableA := context
		newEntityWithDefinitionKey: #demoVisible
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		state: (Dictionary new at: #tag put: #A; yourself).

	notableB := context
		newEntityWithDefinitionKey: #demoInvisible
		transform: (Dictionary new at: #pos put: #(999 0 0); yourself)
		state: (Dictionary new at: #tag put: #B; yourself).

	"Add both notables, but to different regions."
	update := CESimUpdate new.
	update
		addEntityOp: (CESimAddOp withRegionId: regionA aggregateId entity: notableA);
		addEntityOp: (CESimAddOp withRegionId: regionB aggregateId entity: notableB).
	context addUpdate: update.

	engine transactionRunner
		inTransactionDo: [ engine updateApplier applyUpdatesInContext: context ].

	"Capture initial states for mutation assertions."
	stateA0 := notableA state copy.
	stateB0 := notableB state copy.

	"Enqueue stimulus. Module semantics apply ops only to visible snapshots (v0: home region)."
	bubble enqueueCommand: (CESimEmitStimulusAtTransformCommand
		type: #sound
		transform: (Dictionary new at: #pos put: #(0 0 0); yourself)
		intensity: 1).

	view := engine advanceBubbleTickFor: bubble bubbleId.

	^ Dictionary new
		at: #engine put: engine;
		at: #regionA put: regionA;
		at: #regionB put: regionB;
		at: #bubble put: bubble;
		at: #notableA put: notableA;
		at: #notableB put: notableB;
		at: #stateA0 put: stateA0;
		at: #stateB0 put: stateB0;
		at: #view put: view;
		yourself
]

{ #category : 'as yet unclassified' }
CESimExamples >> seedArchetypesAndSpawnSpecsOn: engine [
	engine archetypes
		at: #wolf
		put: (CEEntityArchetype new
				archetypeId: #wolf;
				tags: (OrderedCollection with: #creature with: #agent);
				displayName: 'Wolf';
				yourself).

	engine spawnSpecs
		at: #wolfAdult
		put: (CEEntitySpawnSpec new
				spawnSpecId: #wolfAdult;
				archetypeId: #wolf;
				entityClass: CECreatureEntity;
				appellation: 'Wolf (Adult)';
				initialState: (Dictionary new
						at: #mood put: #neutral;
						yourself);
				moduleSpecs: OrderedCollection new;
				yourself).

	engine spawnSpecs
		at: #demoNotable
		put: (CEEntitySpawnSpec new
				spawnSpecId: #demoNotable;
				archetypeId: #creature;
				entityClass: CECreatureEntity;
				appellation: 'Demo Creature';
				initialState: (Dictionary new
						at: #mood put: #chill;
						yourself);
				moduleSpecs: OrderedCollection new;
				yourself)	"or #wolf etc"
]

{ #category : 'tests' }
CESimExamples >> test_createNotableCommandProducesAuditEventAndSpawn [
	| result view spawn ev |
	result := self example_createNotableCommandProducesAuditEventAndSpawn.
	view := result at: #view.

	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #spawnSpecId) equals: #demoNotable.
	self assert: (spawn includesKey: #entityId).

	ev := view events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #createNotableRequested ]
		ifNone: [ self fail: 'Expected #createNotableRequested event' ].

	self assert: (ev at: #spawnSpecId) equals: #demoNotable
]

{ #category : 'tests' }
CESimExamples >> test_createNotableCommandSpawnsInLocalViewSameTick [
	| view spawn |
	view := self example_createNotableCommandSpawnsInLocalViewSameTick.

	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #spawnSpecId) equals: #demoNotable.
	self assert: (spawn includesKey: #entityId)
]

{ #category : 'tests' }
CESimExamples >> test_inspectEntityRejectedEmitsTargetRejectedAuditEvent [
	| engine region bubble bogusId inspectCmd view ev |
	engine := self example_engineWithCommandDrivenBubblePipeline.
	region := engine newRegion.
	bubble := engine newBubbleInHomeRegionId: region aggregateId.

	"Bogus target: nothing perceived in an empty region."
	bogusId := CEEntityId fromInteger: 9999.
	inspectCmd := CESimInspectEntityCommand targetEntityId: bogusId.

	bubble enqueueCommand: inspectCmd.
	view := engine advanceBubbleTickFor: bubble bubbleId.

	ev := view events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #targetRejected ]
		ifNone: [ self fail: 'Expected #targetRejected event in LocalView events' ].

	self assert: (ev at: #entityId) equals: bogusId.
	self assert: (ev at: #reason) equals: #notPerceived
]

{ #category : 'tests' }
CESimExamples >> test_localViewContainsEntityInspectedEventFromCommand [
	| result view2 entityId ev |
	result := self example_localViewContainsEntityInspectedEventFromCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	ev := view2 events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInspected ]
		ifNone: [ self fail: 'Expected #entityInspected event in LocalView events' ].

	self assert: (ev at: #entityId) equals: entityId.
	self assert: ((ev at: #snapshot) at: #entityId) equals: entityId

]

{ #category : 'tests' }
CESimExamples >> test_localViewContainsEntityInteractionEventFromCommand [
	| result view2 entityId ev |
	result := self example_localViewContainsEntityInteractionEventFromCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	ev := view2 events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInteraction ]
		ifNone: [ self fail: 'Expected #entityInteraction event in LocalView events' ].

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
	result := self example_localViewShowsDeterministicSpawnOrderFromTwoCreateNotableCommands.
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
	self assert: (spawn at: #spawnSpecId) equals: #demoNotable
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsStateUpdateAfterEntityInteractionCommand [
	| result view2 entityId updateSnap state last ev |
	result := self example_localViewShowsStateUpdateAfterEntityInteractionCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.
	self assert: view2 despawns isEmpty.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: entityId.

	state := updateSnap at: #state.
	last := state at: #lastInteraction.

	self assert: (last at: #type) equals: #pet.
	self assert: ((last at: #payload) at: #hand) equals: #right.

	ev := view2 events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInteraction ]
		ifNone: [ self fail: 'Expected #entityInteraction event' ].

	self assert: (ev at: #entityId) equals: entityId.
	self assert: (ev at: #interactionType) equals: #pet
]

{ #category : 'tests' }
CESimExamples >> test_localViewShowsStateUpdateAfterStimulusCommand [
	| result view2 entityId updateSnap state last ev |
	result := self example_localViewShowsStateUpdateAfterStimulusCommand.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.
	self assert: view2 despawns isEmpty.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: entityId.

	state := updateSnap at: #state.
	last := state at: #lastStimulus.

	self assert: (last at: #type) equals: #sound.
	self assert: (last at: #intensity) equals: 0.75.
	self assert: ((last at: #transform) at: #pos) equals: #(5 0 0).

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

{ #category : 'tests' }
CESimExamples >> test_removeNotableCommandDespawnsInLocalViewSameTick [
	| result view2 entityId ev |
	result := self example_removeNotableCommandDespawnsInLocalViewSameTick.
	view2 := result at: #view2.
	entityId := result at: #entityId.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates isEmpty.
	self assert: view2 despawns size equals: 1.
	self assert: view2 despawns first equals: entityId.

	ev := view2 events
		detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #removeNotableRequested ]
		ifNone: [ self fail: 'Expected #removeNotableRequested event' ].

	self assert: (ev at: #entityId) equals: entityId
]

{ #category : 'tests' }
CESimExamples >> test_stimulusOnlyAffectsVisibleNotables [
	| result view notableA notableB stateA0 stateB0 spawn |
	result := self example_stimulusOnlyAffectsVisibleNotables.

	view := result at: #view.
	notableA := result at: #notableA.
	notableB := result at: #notableB.
	stateA0 := result at: #stateA0.
	stateB0 := result at: #stateB0.

	"LocalView should only contain the visible notable (home region only in v0)."
	self assert: view spawns size equals: 1.
	self assert: view updates isEmpty.
	self assert: view despawns isEmpty.

	spawn := view spawns first.
	self assert: (spawn at: #entityId) equals: notableA entityId.

	"Invisible notable must not be mutated by stimulus resolution."
	self assert: notableB state equals: stateB0.

	"Visible notable should have been affected (semantic op applied)."
	self deny: notableA state equals: stateA0.
	self assert: ((notableA state at: #lastStimulus) at: #type) equals: #sound
]
