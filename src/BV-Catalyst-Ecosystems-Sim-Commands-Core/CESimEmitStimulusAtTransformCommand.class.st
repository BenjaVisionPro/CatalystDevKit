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
CESimEmitStimulusAtTransformCommand >> intensity: aNumber [ intensity := aNumber
]

{ #category : 'producing' }
CESimEmitStimulusAtTransformCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
| bubble regionId region |

	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #stimulusEmitted;
		at: #stimulusType put: stimulusType;
		at: #transform put: transform;
		at: #intensity put: intensity;
		at: #tickId put: aCESimRunContext tickId;
		yourself).

	bubble := aCESimRunContext subject.
	regionId := bubble homeRegionId.
	region := aCESimRunContext engine ensureRegion: regionId.

	region notables do: [ :notable |
		| patch newState |
		patch := aCESimRunContext engine stimulusResolver
			patchForStimulusType: stimulusType
			transform: transform
			intensity: intensity
			target: notable
			inContext: aCESimRunContext.

		newState := notable state copy.
		patch keysAndValuesDo: [ :k :v | newState at: k put: v ].

		aCESimUpdate addEntityOp: (CESimSetNotableStateOp
			withRegionId: regionId
			entityId: notable entityId
			state: newState).
	].
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType: aType [ stimulusType := aType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform: aTransform [ transform := aTransform
]
