Class {
	#name : 'CESimApplyStimulusToNotableOp',
	#superclass : 'CESimNotableSemanticStateOp',
	#instVars : [
		'stimulusType',
		'transform',
		'intensity',
		'tickId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimApplyStimulusToNotableOp class >> withRegionId: aCERegionId entityId: aCEEntityId stimulusType: aType transform: aTransform intensity: aNumber tickId: aTickId [
	^ (super withRegionId: aCERegionId entityId: aCEEntityId)
		stimulusType: aType;
		transform: aTransform;
		intensity: aNumber;
		tickId: aTickId;
		yourself
]

{ #category : 'applying' }
CESimApplyStimulusToNotableOp >> applyInContext: aCESimRunContext [
	| state record |
	state := self ensureStateDictInContext: aCESimRunContext.

	record := Dictionary new
		at: #type put: stimulusType;
		at: #transform put: transform;
		at: #intensity put: intensity;
		at: #tickId put: tickId;
		yourself.

	"v0 semantic state: store the last applied stimulus fact."
	state at: #lastStimulus put: record
]

{ #category : 'accessing' }
CESimApplyStimulusToNotableOp >> intensity: aNumber [ 
	intensity := aNumber 
]

{ #category : 'accessing' }
CESimApplyStimulusToNotableOp >> stimulusType: aType [ 
	stimulusType := aType 
]

{ #category : 'accessing' }
CESimApplyStimulusToNotableOp >> tickId: aTickId [ 
	tickId := aTickId 
]

{ #category : 'accessing' }
CESimApplyStimulusToNotableOp >> transform: aTransform [ 
	transform := aTransform 
]
