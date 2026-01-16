Class {
	#name : 'CESimSetNotableStateOp',
	#superclass : 'CESimEntityStateOp',
	#instVars : [
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimSetNotableStateOp class >> withRegionId: aCERegionId entityId: aCEEntityId state: aStateDict [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		state: aStateDict;
		yourself
]

{ #category : 'applying' }
CESimSetNotableStateOp >> applyInContext: aCESimRunContext [
	(self notableInContext: aCESimRunContext) state: state
]

{ #category : 'accessing' }
CESimSetNotableStateOp >> state: aStateDict [
	state := aStateDict
]
