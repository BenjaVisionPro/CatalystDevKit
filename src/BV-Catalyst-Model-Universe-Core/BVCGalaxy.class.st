Class {
	#name : #BVCGalaxy,
	#superclass : #BVCCelestialBody,
	#instVars : [
		'starSystems'
	],
	#category : #'BV-Catalyst-Model-Universe-Core'
}

{ #category : #accessing }
BVCGalaxy >> starSystems [
	^ starSystems ifNil: [ starSystems := OrderedCollection new ]
]
