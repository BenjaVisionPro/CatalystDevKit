Class {
	#name : 'CESimBuildLocalViewStageRunner',
	#superclass : 'CESimStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimBuildLocalViewStageRunner >> runStage: aStage inContext: aContext [
	| subject snapshots previousIds previousMap currentIds spawns updates despawns allEvents view |
	subject := aContext subject.	
	
	"Post-stage snapshots must already be deterministic-ordered by the collector stage."
	snapshots := aContext postEntitySnapshots.
	snapshots ifNil: [ snapshots := #() ].	
	
	"Previous visible ids are durable bubble state."
	previousIds := subject visibleEntityIds.

	previousMap := Dictionary new: previousIds size.
	previousIds do: [ :id | previousMap at: id put: true ].

	currentIds := OrderedCollection new: snapshots size.
	spawns := OrderedCollection new.
	updates := OrderedCollection new.

	snapshots
		do: [ :snap | 
			| id |
			id := snap at: #entityId.
			currentIds add: id.

			(previousMap includesKey: id)
				ifTrue: [ previousMap removeKey: id.
					updates add: snap ]
				ifFalse: [ spawns add: snap ] ].

	despawns := OrderedCollection new.
	previousIds
		do: [ :id | (previousMap includesKey: id) ifTrue: [ despawns add: id ] ].

	allEvents := aContext tickEvents.
	allEvents ifNil: [ allEvents := #() ].

	view := CESimLocalView new
			bubbleId: subject bubbleId;
			tickId: aContext tickId;
			events: allEvents;
			spawns: spawns;
			updates: updates;
			despawns: despawns;
			yourself.

	aContext localView: view
]
