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

	^ Dictionary new
		at: #entityId put: entityId;
		at: #definitionKey put: definitionKey;
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
