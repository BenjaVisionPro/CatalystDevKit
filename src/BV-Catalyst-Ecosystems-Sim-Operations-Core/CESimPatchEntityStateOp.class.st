Class {
	#name : 'CESimPatchEntityStateOp',
	#superclass : 'CESimEntityStateOp',
	#instVars : [
		'patch'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Operations-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
}

{ #category : 'instance creation' }
CESimPatchEntityStateOp class >> withRegionId: aCERegionId entityId: aCEEntityId patch: aPatchDict [
	^ (super withRegionId: aCERegionId entityId: aCEEntityId)
		patch: aPatchDict;
		yourself
]

{ #category : 'applying' }
CESimPatchEntityStateOp >> applyInContext: aCESimRunContext [
	self subclassResponsibility
]

{ #category : 'accessing' }
CESimPatchEntityStateOp >> patch [
	^ patch
]

{ #category : 'accessing' }
CESimPatchEntityStateOp >> patch: anObject [
	patch := anObject
]
