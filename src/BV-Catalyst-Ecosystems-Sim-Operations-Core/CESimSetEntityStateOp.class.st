Class {
	#name : 'CESimSetEntityStateOp',
	#superclass : 'CESimEntityStateOp',
	#instVars : [
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimSetEntityStateOp class >> withRegionId: aCERegionId entityId: aCEEntityId state: aStateDict [
	^ self new
		regionId: aCERegionId;
		entityId: aCEEntityId;
		state: aStateDict;
		yourself
]

{ #category : 'applying' }
CESimSetEntityStateOp >> applyInContext: aCESimRunContext [
	(self entityInContext: aCESimRunContext) state: state
]

{ #category : 'accessing' }
CESimSetEntityStateOp >> state: aStateDict [
	state := aStateDict
]
