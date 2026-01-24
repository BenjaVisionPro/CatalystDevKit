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

{ #category : 'convertion' }
CESimSpatialEntity >> asSnapshot [
	"Authoritative sim-space snapshot (no UE types)."

	^ super asSnapshot
		at: #transform put: transform;
		at: #velocity put: velocity;
		yourself
]

{ #category : 'spawning' }
CESimSpatialEntity >> configureFromSpawnSpec: aSpec entityId: anId transform: aTransform [
	super
		configureFromSpawnSpec: aSpec
		entityId: anId
		transform: aTransform.
	transform := aTransform.
	^ self
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
