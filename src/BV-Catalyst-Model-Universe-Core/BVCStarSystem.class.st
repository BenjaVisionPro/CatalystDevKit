Class {
	#name : #BVCStarSystem,
	#superclass : #BVCCelestialBody,
	#instVars : [
		'bodies'
	],
	#category : #'BV-Catalyst-Model-Universe-Core'
}

{ #category : #'as yet unclassified' }
BVCStarSystem >> initialize [
	super initialize.
	bodies := OrderedCollection new.
]
