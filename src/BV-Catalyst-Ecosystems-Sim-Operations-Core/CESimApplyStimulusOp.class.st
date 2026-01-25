Class {
	#name : 'CESimApplyStimulusOp',
	#superclass : 'CESimStateOp',
	#instVars : [
		'stimulusType',
		'transform',
		'intensity',
		'tickId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'applying' }
CESimApplyStimulusOp >> applyInContext: aCESimRunContext [
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
CESimApplyStimulusOp >> intensity: aNumber [ 
	intensity := aNumber 
]

{ #category : 'accessing' }
CESimApplyStimulusOp >> stimulusType: aType [ 
	stimulusType := aType 
]

{ #category : 'accessing' }
CESimApplyStimulusOp >> tickId: aTickId [ 
	tickId := aTickId 
]

{ #category : 'accessing' }
CESimApplyStimulusOp >> transform: aTransform [ 
	transform := aTransform 
]
