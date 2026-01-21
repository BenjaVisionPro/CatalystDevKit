Class {
	#name : 'CESimEmitStimulusAtTransformCommand',
	#superclass : 'CESimExternalCommand',
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

{ #category : 'contributing' }
CESimEmitStimulusAtTransformCommand >> contributeStimulusIntoUpdate: aSimUpdate inContext: aSimContext [
	(aSimContext runCache perceivedVisibleSnapshots ifNil: [ #() ])
		do: [ :snapshot | 
			aSimUpdate
				addEntityOp: (CESimApplyStimulusToNotableOp
						withRegionId: aSimContext subject homeRegionId
						entityId: (snapshot at: #entityId)
						stimulusType: stimulusType
						transform: transform
						intensity: intensity
						tickId: aSimContext tickId) ]
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> intensity [
	^ intensity
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> intensity: aNumber [
	intensity := aNumber
]

{ #category : 'producing' }
CESimEmitStimulusAtTransformCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #stimulusEmitted;
		at: #stimulusType put: stimulusType;
		at: #transform put: transform;
		at: #intensity put: intensity;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType [
	^ stimulusType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType: aType [
	stimulusType := aType
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform: aTransform [
	transform := aTransform
]
