"
I am the root of the GearItem hierarchy. GearItems are objects that can be part of a Gear Ensemble. There are many ""slots"" in a Gear Ensemble, each accepting a subset of GearItem types. eg. The ""Backpack"" slot accepts GearItems that are instances on BVCBackpack or one of its subclasses.s
"
Class {
	#name : #BVCGearItem,
	#superclass : #BVCObjectWithTitleAndComment,
	#category : #'BV-Catalyst-UE-Core'
}

{ #category : #sockets }
BVCGearItem >> sockets [
	"Which sockets can this gear item be attached to"
	^ self subclassResponsibility
]
