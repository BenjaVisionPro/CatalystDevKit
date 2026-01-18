Class {
	#name : 'CESimBehaviour',
	#superclass : 'Object',
	#instVars : [
		'stimulusResolver',
		'interactionResolver'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimBehaviour >> initialize [
	super initialize.
	stimulusResolver := CESimStimulusResolver new.
	interactionResolver := CESimInteractionResolver new
]

{ #category : 'interaction' }
CESimBehaviour >> patchForInteractionType: anInteractionType payload: aPayload target: aTarget inContext: aCESimRunContext [
	^ interactionResolver
		patchForInteractionType: anInteractionType
		payload: aPayload
		target: aTarget
		inContext: aCESimRunContext
]

{ #category : 'stimuli' }
CESimBehaviour >> patchForStimulusType: aType transform: aTransform intensity: aNumber target: aTarget inContext: aCESimRunContext [
	^ stimulusResolver
		patchForStimulusType: aType
		transform: aTransform
		intensity: aNumber
		target: aTarget
		inContext: aCESimRunContext
]

{ #category : 'commands' }
CESimBehaviour >> produceOperationsForCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCommand
		produceOperationsViaBehaviour: self
		intoUpdate: aCESimUpdate
		inContext: aCESimRunContext
]

{ #category : 'stimuli' }
CESimBehaviour >> produceOperationsForEmitStimulusAtTransformCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| visibleSnapshots bubble regionId engine region |
	visibleSnapshots := aCESimRunContext runCache visibleSnapshots.

	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.

	engine := aCESimRunContext engine.
	region := engine ensureRegion: regionId.

	visibleSnapshots
		do: [ :snap | 
			| entityId notable patch |
			entityId := snap at: #entityId.
			notable := region notableAt: entityId.

			patch := self
					patchForStimulusType: aCommand stimulusType
					transform: aCommand transform
					intensity: aCommand intensity
					target: notable
					inContext: aCESimRunContext.

			aCESimUpdate
				addEntityOp: (CESimPatchNotableStateOp
						withRegionId: regionId
						entityId: entityId
						patch: patch) ]
]

{ #category : 'interaction' }
CESimBehaviour >> produceOperationsForInteractWithEntityCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| bubble regionId engine region notable patch entityId |
	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.

	engine := aCESimRunContext engine.
	region := engine ensureRegion: regionId.

	entityId := aCommand targetEntityId.
	notable := region notableAt: entityId.

	patch := self
			patchForInteractionType: aCommand interactionType
			payload: aCommand payload
			target: notable
			inContext: aCESimRunContext.

	aCESimUpdate
		addEntityOp: (CESimPatchNotableStateOp
				withRegionId: regionId
				entityId: entityId
				patch: patch)
]
