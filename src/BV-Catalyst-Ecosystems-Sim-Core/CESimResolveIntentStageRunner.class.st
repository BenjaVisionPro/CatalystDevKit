Class {
	#name : 'CESimResolveIntentStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'private - resolving' }
CESimResolveIntentStageRunner >> addInteractionOpsFrom: anInteractionCommand regionId: aRegionId context: aCESimRunContext intoUpdate: aCESimUpdate [
	| engine region notable patch entityId |
	engine := aCESimRunContext engine.
	region := engine ensureRegion: aRegionId.

	entityId := anInteractionCommand targetEntityId.
	notable := region notableAt: entityId.

	patch := engine interactionResolver
		patchForInteractionType: anInteractionCommand interactionType
		payload: anInteractionCommand payload
		target: notable
		inContext: aCESimRunContext.

	aCESimUpdate addEntityOp: (CESimPatchNotableStateOp
		withRegionId: aRegionId
		entityId: entityId
		patch: patch).
]

{ #category : 'private - resolving' }
CESimResolveIntentStageRunner >> addStimulusOpsFrom: aStimulusCommand visibleSnapshots: visibleSnapshots regionId: aRegionId context: aCESimRunContext intoUpdate: aCESimUpdate [
	| engine region |
	engine := aCESimRunContext engine.
	region := engine ensureRegion: aRegionId.

	visibleSnapshots
		do: [ :snap | 
			| entityId notable patch |
			entityId := snap at: #entityId.
			notable := region notableAt: entityId.

			patch := engine stimulusResolver
					patchForStimulusType: aStimulusCommand stimulusType
					transform: aStimulusCommand transform
					intensity: aStimulusCommand intensity
					target: notable
					inContext: aCESimRunContext.

			aCESimUpdate
				addEntityOp: (CESimPatchNotableStateOp
						withRegionId: aRegionId
						entityId: entityId
						patch: patch) ]
]

{ #category : 'running' }
CESimResolveIntentStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
	| commands visibleSnapshots bubble regionId update |
	commands := aCESimRunContext
			stepCacheAt: #drainedCommands
			ifAbsent: [ OrderedCollection new ].

	commands isEmpty ifTrue: [ ^ CESimUpdate new ].

	visibleSnapshots := aCESimRunContext
			stepCacheAt: #visibleSnapshots
			ifAbsent: [ OrderedCollection new ].

	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.

	update := CESimUpdate new.

	commands
		do: [ :cmd | 
			cmd produceIntoUpdate: update inContext: aCESimRunContext.	"events"
			cmd produceIntentOpsIntoUpdate: update inContext: aCESimRunContext	"ops" ].
	^ update
]
