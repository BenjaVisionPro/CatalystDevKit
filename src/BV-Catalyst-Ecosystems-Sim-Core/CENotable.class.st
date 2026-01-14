Class {
	#name : 'CENotable',
	#superclass : 'CESimSpatialEntity',
	#instVars : [
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CENotable class >> id: aCEEntityId definitionKey: aDefinitionKey transform: aTransformDict state: aStateDict [
	^ (super id: aCEEntityId definitionKey: aDefinitionKey)
		transform: aTransformDict;
		state: aStateDict;
		yourself
]

{ #category : 'convertion' }
CENotable >> asSnapshot [
	| snap |
	snap := super asSnapshot.
	snap at: #state put: state.
	^ snap
]

{ #category : 'accessing' }
CENotable >> state [
	^ state
]

{ #category : 'accessing' }
CENotable >> state: anObject [
	state := anObject
]
