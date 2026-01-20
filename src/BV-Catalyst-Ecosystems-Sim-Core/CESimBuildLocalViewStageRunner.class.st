Class {
	#name : 'CESimBuildLocalViewStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimBuildLocalViewStageRunner >> runStage: aStage inContext: aCESimRunContext [
	| bubble snapshots previousIds previousMap currentIds spawns updates despawns allEvents view |
	bubble := aCESimRunContext subject.

	"Snapshots must be provided in deterministic order by the collector stage."
	snapshots := aCESimRunContext runCache visibleSnapshots.

	"Previous visible ids are durable bubble state."
	previousIds := bubble visibleEntityIds.

	previousMap := Dictionary new: previousIds size.
	previousIds do: [ :id | previousMap at: id put: true ].

	currentIds := OrderedCollection new: snapshots size.
	spawns := OrderedCollection new.
	updates := OrderedCollection new.

	snapshots do: [ :snap |
		| id |
		id := snap at: #entityId.
		currentIds add: id.

		(previousMap includesKey: id)
			ifTrue: [ previousMap removeKey: id. updates add: snap ]
			ifFalse: [ spawns add: snap ] ].

	despawns := OrderedCollection new.
	previousIds do: [ :id | (previousMap includesKey: id) ifTrue: [ despawns add: id ] ].

	"Events from this tick’s authoritative update(s)."
	allEvents := aCESimRunContext runCache tickEvents.

	view := CESimLocalView new
		bubbleId: bubble bubbleId;
		tickId: aCESimRunContext tickId;
		events: allEvents;
		spawns: spawns;
		updates: updates;
		despawns: despawns;
		yourself.

	bubble setVisibleEntityIds: currentIds.
	aCESimRunContext runCache result: view
]
