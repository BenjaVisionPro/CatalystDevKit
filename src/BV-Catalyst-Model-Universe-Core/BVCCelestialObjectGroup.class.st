Class {
	#name : #BVCCelestialObjectGroup,
	#superclass : #BVCCelestialObject,
	#instVars : [
		'children'
	],
	#category : #'BV-Catalyst-Model-Universe-Core'
}

{ #category : #'as yet unclassified' }
BVCCelestialObjectGroup >> initialize [
	super initialize.
	children := Set new.
]
