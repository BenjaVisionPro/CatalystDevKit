Class {
	#name : #BVCDevKitWorld,
	#superclass : #GtWorld,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #accessing }
BVCDevKitWorld class >> defaultTitle [
	^ 'BenjaVision Catalyst DevKit'
]

{ #category : #initialization }
BVCDevKitWorld >> defaultWorldElement [
	^ BVCDevKitWorldElement new
]

{ #category : #initialization }
BVCDevKitWorld >> initialize [
	super initialize.
	self markAsDefault.
	self updateWorldContent
]
