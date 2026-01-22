Class {
	#name : 'CESimEmitStimulusAtTransformInvocation',
	#superclass : 'CESimStimulusInvocation',
	#instVars : [
		'stimulusType',
		'transform',
		'intensity'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimEmitStimulusAtTransformInvocation class >> stimulusType: aType transform: aTransform intensity: aNumber [
	^ self new
		stimulusType: aType;
		transform: aTransform;
		intensity: aNumber;
		yourself
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> stimulusType: aType [
	stimulusType := aType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> transform: aTransform [
	transform := aTransform
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> intensity: aNumber [
	intensity := aNumber
]

{ #category : 'contributing' }
CESimEmitStimulusAtTransformInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| snapshots |

	snapshots := aSimContext runCache perceivedVisibleSnapshots ifNil: [ #() ].

	snapshots do: [ :snap |
		aSimUpdate addEntityOp: (CESimApplyStimulusToNotableOp
			withRegionId: aSimContext homeRegionId
			entityId: (snap at: #entityId)
			stimulusType: stimulusType
			transform: transform
			intensity: intensity
			tickId: aSimContext tickId)
	]
]