Class {
	#name : 'CESimEmitStimulusAtTransformCommand',
	#superclass : 'CESimStimulusCommand',
	#instVars : [
		'stimulusType',
		'transform',
		'intensity'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimEmitStimulusAtTransformCommand class >> type: aType transform: aTransform intensity: aNumber [
  ^ self new
    stimulusType: aType;
    transform: aTransform;
    intensity: aNumber;
    yourself
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> intensity [
	^ intensity
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> intensity: aNumber [ intensity := aNumber
]

{ #category : 'producing' }
CESimEmitStimulusAtTransformCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate
		addEvent: (Dictionary new
				at: #type put: #stimulusEmitted;
				at: #stimulusType put: stimulusType;
				at: #transform put: transform;
				at: #intensity put: intensity;
				at: #tickId put: aCESimRunContext tickId;
				yourself)
]

{ #category : 'producing' }
CESimEmitStimulusAtTransformCommand >> produceOperationsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
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

			patch := engine stimulusResolver
					patchForStimulusType: self stimulusType
					transform: self transform
					intensity: self intensity
					target: notable
					inContext: aCESimRunContext.

			aCESimUpdate
				addEntityOp: (CESimPatchNotableStateOp
						withRegionId: regionId
						entityId: entityId
						patch: patch) ]
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType [
	^ stimulusType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType: aType [ stimulusType := aType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform: aTransform [ transform := aTransform
]
