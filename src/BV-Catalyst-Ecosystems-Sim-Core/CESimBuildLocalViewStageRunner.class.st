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
	
	"Snapshots must be provided in deterministic order by the collector stage.
     (Later: selector ordering / stable sort by entity id or spatial key.)"
	snapshots := aCESimRunContext
			stepCacheAt: #visibleSnapshots
			ifAbsent: [ OrderedCollection new ].	
			
	"Previous visible ids are durable bubble state (not stepCache)."
	previousIds := bubble visibleEntityIds.	
	
	"Mark-table for diff: keys remaining after the pass are despawns."
	previousMap := Dictionary new: previousIds size.
	previousIds do: [ :id | previousMap at: id put: true ].

	currentIds := OrderedCollection new: snapshots size.
	spawns := OrderedCollection new.
	updates := OrderedCollection new.	
	
	"Single pass over current snapshots:
     - if id was previously visible -> update, and remove from previousMap
     - else -> spawn"
	snapshots
		do: [ :snap | 
			| id |
			id := snap at: #entityId.
			currentIds add: id.

			(previousMap includesKey: id)
				ifTrue: [ previousMap removeKey: id.
					updates add: snap ]
				ifFalse: [ spawns add: snap ] ].	
				
	"Despawn order follows previousIds order for stability."
	despawns := OrderedCollection new.
	previousIds
		do: [ :id | (previousMap includesKey: id) ifTrue: [ despawns add: id ] ].	
		
	"Events from this bubble advance (authoritative outcomes)."
	allEvents := aCESimRunContext
			stepCacheAt: #tickEvents
			ifAbsent: [ | ev |
				ev := OrderedCollection new.
				aCESimRunContext updates do: [ :eachUpdate | ev addAll: eachUpdate events ].
				ev ].

	view := CESimLocalView new
			bubbleId: bubble bubbleId;
			tickId: aCESimRunContext tickId;
			events: allEvents;
			spawns: spawns;
			updates: updates;
			despawns: despawns;
			yourself.	
	
	"Persist the visible set for the next diff."
	bubble setVisibleEntityIds: currentIds.	"Publish result for the engine boundary."
	aCESimRunContext stepCacheAt: #result put: view
]
