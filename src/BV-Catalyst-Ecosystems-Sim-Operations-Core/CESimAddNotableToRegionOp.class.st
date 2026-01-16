Class {
	#name : 'CESimAddNotableToRegionOp',
	#superclass : 'CESimEntityLifecycleOp',
	#instVars : [
		'notable'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimAddNotableToRegionOp class >> withRegionId: aCERegionId notable: aCENotable [
	^ self new
		regionId: aCERegionId;
		entityId: aCENotable entityId;
		notable: aCENotable;
		yourself
]

{ #category : 'applying' }
CESimAddNotableToRegionOp >> applyInContext: aCESimRunContext [
	(self regionInContext: aCESimRunContext) addNotable: notable
]

{ #category : 'accessing' }
CESimAddNotableToRegionOp >> notable: aCENotable [
	notable := aCENotable
]
