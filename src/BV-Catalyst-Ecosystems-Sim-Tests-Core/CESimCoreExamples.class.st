Class {
	#name : 'CESimCoreExamples',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Ecosystems-Sim-Tests-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
}

{ #category : 'examples' }
CESimCoreExamples >> example_coreEngine [
	<gtExample>
	| engine pipeline stages |
	engine := CESimEngine new.

	stages := OrderedCollection new.
	stages
		add: (CESimStage new
				stageId: #collectPreEntitySnapshots;
				runner: CESimCollectPreEntitySnapshotsStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #executeCommandInput;
				runner: CESimExecuteCommandInputStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #applyUpdates;
				runner: CESimApplyUpdatesStageRunner new;
				yourself);
		add: (CESimStage new
				stageId: #collectPostEntitySnapshots;
				runner: CESimCollectPostEntitySnapshotsStageRunner new;
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

	^ Dictionary new
		at: #engine put: engine;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_coreEngineWithOnePartitionAndBubble [
	<gtExample>
	| engine partition bubble |
	engine := self example_coreEngine at: #engine.
	partition := engine newPartition.
	bubble := engine newBubbleInPartitionId: partition partitionId.

	^ Dictionary new
		at: #engine put: engine;
		at: #partition put: partition;
		at: #bubble put: bubble;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_inspectRejected_tick1_emptyWorld [
	<gtExample>
	| seed engine bubble bogusId inspectCmd context1 view1 rejectionEvent |
	seed := self example_coreEngineWithOnePartitionAndBubble.
	engine := seed at: #engine.
	bubble := seed at: #bubble.

	bogusId := CEEntityId fromInteger: 9999.
	inspectCmd := CESimInspectEntityCommand targetEntityId: bogusId.
	bubble enqueueCommand: inspectCmd.

	context1 := engine advanceTickForBubbleId: bubble bubbleId.
	view1 := context1 localView.

	rejectionEvent := view1 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #targetRejected ]
			ifNone: [ nil ].

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #bogusId put: bogusId;
		at: #context1 put: context1;
		at: #view1 put: view1;
		at: #rejectionEvent put: rejectionEvent;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_spawnOneEntity_tick1 [
	<gtExample>
	| seed engine partition bubble cmd context1 view1 entityId |
	seed := self example_coreEngineWithOnePartitionAndBubble.
	engine := seed at: #engine.
	partition := seed at: #partition.
	bubble := seed at: #bubble.

	cmd := CESimAddEntityCommand
			withSpawnSpecId: #demoCreature
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			stateOverlay: (Dictionary new
					at: #mood put: #chill;
					yourself).

	bubble enqueueCommand: cmd.

	context1 := engine advanceTickForBubbleId: bubble bubbleId.
	view1 := context1 localView.
	entityId := view1 spawns first at: #entityId.

	^ Dictionary new
		at: #engine put: engine;
		at: #partition put: partition;
		at: #bubble put: bubble;
		at: #context1 put: context1;
		at: #view1 put: view1;
		at: #entityId put: entityId;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_spawnThenInspect_tick2 [
	<gtExample>
	| seed engine bubble entityId inspectCmd context2 view2 inspectEvent |
	seed := self example_spawnOneEntity_tick1.
	engine := seed at: #engine.
	bubble := seed at: #bubble.
	entityId := seed at: #entityId.

	inspectCmd := CESimInspectEntityCommand targetEntityId: entityId.
	bubble enqueueCommand: inspectCmd.

	context2 := engine advanceTickForBubbleId: bubble bubbleId.
	view2 := context2 localView.

	inspectEvent := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInspected ]
			ifNone: [ nil ].

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #entityId put: entityId;
		at: #context2 put: context2;
		at: #view2 put: view2;
		at: #inspectEvent put: inspectEvent;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_spawnThenRemove_tick2 [
	<gtExample>
	| seed engine bubble entityId removeCmd context2 view2 |
	seed := self example_spawnOneEntity_tick1.
	engine := seed at: #engine.
	bubble := seed at: #bubble.
	entityId := seed at: #entityId.

	removeCmd := CESimRemoveEntityCommand targetEntityId: entityId.
	bubble enqueueCommand: removeCmd.

	context2 := engine advanceTickForBubbleId: bubble bubbleId.
	view2 := context2 localView.

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #removedEntityId put: entityId;
		at: #context2 put: context2;
		at: #view2 put: view2;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_spawnThenTransform_tick2 [
	<gtExample>
	| seed engine bubble entityId transform2 transformCmd context2 view2 |
	seed := self example_spawnOneEntity_tick1.
	engine := seed at: #engine.
	bubble := seed at: #bubble.
	entityId := seed at: #entityId.

	transform2 := Dictionary new
			at: #pos put: #(10 0 0);
			yourself.

	transformCmd := CESimTransformEntityCommand
			targetEntityId: entityId
			transform: transform2.

	bubble enqueueCommand: transformCmd.

	context2 := engine advanceTickForBubbleId: bubble bubbleId.
	view2 := context2 localView.

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #entityId put: entityId;
		at: #transform2 put: transform2;
		at: #context2 put: context2;
		at: #view2 put: view2;
		yourself
]

{ #category : 'examples' }
CESimCoreExamples >> example_spawnTwoEntitiesSameTick_deterministicOrder [
	<gtExample>
	| seed engine bubble cmd1 cmd2 context1 view1 spawns ids |
	seed := self example_coreEngineWithOnePartitionAndBubble.
	engine := seed at: #engine.
	bubble := seed at: #bubble.

	cmd1 := CESimAddEntityCommand
			withSpawnSpecId: #demoCreature
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself)
			stateOverlay: (Dictionary new
					at: #tag put: #A;
					yourself).

	cmd2 := CESimAddEntityCommand
			withSpawnSpecId: #demoCreature
			transform: (Dictionary new
					at: #pos put: #(1 0 0);
					yourself)
			stateOverlay: (Dictionary new
					at: #tag put: #B;
					yourself).

	bubble enqueueCommand: cmd1.
	bubble enqueueCommand: cmd2.

	context1 := engine advanceTickForBubbleId: bubble bubbleId.
	view1 := context1 localView.
	spawns := view1 spawns.
	ids := spawns collect: [ :each | each at: #entityId ].

	^ Dictionary new
		at: #engine put: engine;
		at: #bubble put: bubble;
		at: #context1 put: context1;
		at: #view1 put: view1;
		at: #spawns put: spawns;
		at: #entityIds put: ids;
		yourself
]

{ #category : 'support' }
CESimCoreExamples >> seedArchetypesAndSpawnSpecsOn: engine [
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
		at: #demoCreature
		put: (CEEntitySpawnSpec new
			spawnSpecId: #demoCreature;
			archetypeId: #creature;
			entityClass: CECreatureEntity;
			appellation: 'Demo Creature';
			initialState: (Dictionary new
				at: #mood put: #chill;
				yourself);
			moduleSpecs: OrderedCollection new;
			yourself)
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_coreEngineWithOnePartitionAndBubble_createsAggregates [
	| seed engine partition bubble |
	seed := self example_coreEngineWithOnePartitionAndBubble.
	engine := seed at: #engine.
	partition := seed at: #partition.
	bubble := seed at: #bubble.

	self assert: (engine hasBubbleId: bubble bubbleId).
	self
		assert: ((engine partitions includes: partition)
				or: [ engine partitions anySatisfy: [ :p | p partitionId = partition partitionId ] ]).
	self assert: bubble partitionId equals: partition partitionId
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_coreEngine_seedsPipelineAndSpawnSpecs [
	| seed engine |
	seed := self example_coreEngine.
	engine := seed at: #engine.

	self assert: engine bubblePipeline notNil.
	self assert: (engine spawnSpecs includesKey: #demoCreature)
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_inspectRejected_tick1_emptyWorld_emitsTargetRejected [
	| seed rejection |
	seed := self example_inspectRejected_tick1_emptyWorld.
	rejection := seed at: #rejectionEvent.

	self assert: rejection notNil.
	self assert: (rejection at: #type) equals: #targetRejected.
	self assert: (rejection includesKey: #reason)
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnOneEntity_tick1_persistsInPartition [
	| seed partition entityId |
	seed := self example_spawnOneEntity_tick1.
	partition := seed at: #partition.
	entityId := seed at: #entityId.

	self assert: (partition includesEntityId: entityId)
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnOneEntity_tick1_spawnsAndProducesAuditEvent [
	| seed view1 spawn audit |
	seed := self example_spawnOneEntity_tick1.
	view1 := seed at: #view1.

	self assert: view1 spawns size equals: 1.
	self assert: view1 updates isEmpty.
	self assert: view1 despawns isEmpty.

	spawn := view1 spawns first.
	self assert: (spawn at: #spawnSpecId) equals: #demoCreature.
	self assert: (spawn includesKey: #entityId).
	self assert: (spawn includesKey: #transform).
	self assert: (spawn includesKey: #state).

	audit := view1 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #addEntityRequested ]
			ifNone: [ self fail: 'Expected #addEntityRequested event' ].

	self assert: (audit at: #spawnSpecId) equals: #demoCreature.
	self assert: (audit at: #entityId) isNil.
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnThenInspect_tick2_emitsInspectRequestedAndEntityInspected [
	| seed view2 entityId request inspected |
	seed := self example_spawnThenInspect_tick2.
	view2 := seed at: #view2.
	entityId := seed at: #entityId.

	request := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #inspectEntityRequested ]
			ifNone: [ self fail: 'Expected #inspectEntityRequested event' ].

	self assert: (request at: #entityId) equals: entityId.

	inspected := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #entityInspected ]
			ifNone: [ self fail: 'Expected #entityInspected event' ].

	self assert: (inspected at: #entityId) equals: entityId.
	self assert: ((inspected at: #snapshot) at: #entityId) equals: entityId
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnThenRemove_tick2_despawnsAndRemovesFromPartition [
	| seed engine bubble removedId view2 partition removeAudit |
	seed := self example_spawnThenRemove_tick2.

	engine := seed at: #engine.
	bubble := seed at: #bubble.
	removedId := seed at: #removedEntityId.
	view2 := seed at: #view2.

	partition := engine ensurePartition: bubble partitionId.

	self assert: (view2 despawns includes: removedId).
	self assert: (partition includesEntityId: removedId) equals: false.

	removeAudit := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #removeEntityRequested ]
			ifNone: [ self fail: 'Expected #removeEntityRequested event' ].

	self assert: (removeAudit at: #entityId) equals: removedId
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnThenTransform_tick2_producesUpdateWithNewTransform [
	| seed view2 entityId transform2 updateSnap audit |
	seed := self example_spawnThenTransform_tick2.
	view2 := seed at: #view2.
	entityId := seed at: #entityId.
	transform2 := seed at: #transform2.

	self assert: view2 spawns isEmpty.
	self assert: view2 updates size equals: 1.

	updateSnap := view2 updates first.
	self assert: (updateSnap at: #entityId) equals: entityId.
	self assert: (updateSnap at: #transform) equals: transform2.

	audit := view2 events
			detect: [ :e | (e at: #type ifAbsent: [ nil ]) = #transformEntityRequested ]
			ifNone: [ self fail: 'Expected #transformEntityRequested event' ].

	self assert: (audit at: #entityId) equals: entityId.
	self assert: (audit at: #transform) equals: transform2
]

{ #category : 'tests' }
CESimCoreExamples >> test_example_spawnTwoEntitiesSameTick_deterministicOrderByEntityIdValue [
	| seed ids |
	seed := self example_spawnTwoEntitiesSameTick_deterministicOrder.
	ids := seed at: #entityIds.

	self assert: ids size equals: 2.
	self assert: ids first value < ids second value
]

{ #category : 'tests' }
CESimCoreExamples >> test_opOrdering_acrossOpOrder_lifecycleBeforeSpatial [
	| engine id1 e1 lifecycleOp spatialOp |
	engine := CESimEngine new.
	id1 := engine idIssuer nextEntityId.

	e1 := CECreatureEntity new
			entityId: id1;
			spawnSpecId: #demoCreature;
			state: Dictionary new;
			yourself.

	lifecycleOp := CESimAddOp entity: e1.
	spatialOp := CESimSetTransformOp
			entityId: id1
			transform: (Dictionary new
					at: #pos put: #(0 0 0);
					yourself).	"Lifecycle must apply before spatial regardless of id."
	self assert: (lifecycleOp before: spatialOp)
]

{ #category : 'tests' }
CESimCoreExamples >> test_opOrdering_withinSameOpOrder_sortsByEntityIdValue [
	| engine id1 id2 e1 e2 op1 op2 |
	engine := CESimEngine new.

	id1 := engine idIssuer nextEntityId.
	id2 := engine idIssuer nextEntityId.

	self assert: id1 value < id2 value.

	e1 := CECreatureEntity new
			entityId: id1;
			spawnSpecId: #demoCreature;
			state: Dictionary new;
			yourself.

	e2 := CECreatureEntity new
			entityId: id2;
			spawnSpecId: #demoCreature;
			state: Dictionary new;
			yourself.	"Both are lifecycle ops (same opOrder). Must sort by entityId."
	op1 := CESimAddOp entity: e1.
	op2 := CESimAddOp entity: e2.

	self assert: (op1 before: op2)
]

{ #category : 'tests' }
CESimCoreExamples >> test_partitionContainingEntityId_usesStablePartitionsEnumeration [
	| engine p1 p2 entityId entity found |
	engine := CESimEnginePartitionScanSpy new.

	p1 := engine newPartition.
	p2 := engine newPartition.

	entityId := engine idIssuer nextEntityId.
	entity := CECreatureEntity new
			entityId: entityId;
			spawnSpecId: #demoCreature;
			state: Dictionary new;
			yourself.	"Put the entity in p2 so lookup must find p2"
	p2 addEntity: entity.

	found := engine
			partitionContainingEntityId: entityId
			ifNone: [ self fail: 'Expected to find a partition containing the entity.' ].

	self assert: engine partitionsWasCalled.
	self assert: found equals: p2
]
