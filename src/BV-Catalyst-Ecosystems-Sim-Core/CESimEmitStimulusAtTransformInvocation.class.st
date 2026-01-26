Class {
	#name : 'CESimEmitStimulusAtTransformInvocation',
	#superclass : 'CESimInvocation',
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

{ #category : 'contributing' }
CESimEmitStimulusAtTransformInvocation >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| snapshots |

	snapshots := aSimContext runCache perceivedSnapshots.

	snapshots do: [ :snap |
		aSimUpdate addEntityOp: (CESimApplyStimulusOp
			withRegionId: aSimContext partitionId
			entityId: (snap at: #entityId)
			stimulusType: stimulusType
			transform: transform
			intensity: intensity
			tickId: aSimContext tickId)
	]
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> intensity: aNumber [
	intensity := aNumber
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> stimulusType: aType [
	stimulusType := aType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformInvocation >> transform: aTransform [
	transform := aTransform
]
