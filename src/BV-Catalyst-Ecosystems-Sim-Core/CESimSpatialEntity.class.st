Class {
	#name : 'CESimSpatialEntity',
	#superclass : 'CESimEntity',
	#instVars : [
		'transform',
		'velocity'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimSpatialEntity class >> spawnFromSpec: aSpec entityId: anEntityId transform: aTransform state: aState [
	| entity |
	entity := super
			spawnFromSpec: aSpec
			entityId: anEntityId
			transform: aTransform
			state: aState.
	entity applySpawnTransform: aTransform.
	^ entity
]

{ #category : 'transforming' }
CESimSpatialEntity >> applySpawnTransform: aTransform [
	self transform: aTransform
]

{ #category : 'transforming' }
CESimSpatialEntity >> applyTransform: aTransform [
	self transform: aTransform
]

{ #category : 'convertion' }
CESimSpatialEntity >> asSnapshot [
	"Authoritative sim-space snapshot (no UE types)."

	^ super asSnapshot
		at: #transform put: transform;
		at: #velocity put: velocity;
		yourself
]

{ #category : 'accessing' }
CESimSpatialEntity >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimSpatialEntity >> transform: anObject [
	transform := anObject
]

{ #category : 'accessing' }
CESimSpatialEntity >> velocity [
	^ velocity
]

{ #category : 'accessing' }
CESimSpatialEntity >> velocity: anObject [
	velocity := anObject
]
