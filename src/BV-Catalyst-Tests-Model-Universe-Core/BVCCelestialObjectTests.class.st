Class {
	#name : #BVCCelestialObjectTests,
	#superclass : #TestCase,
	#category : #'BV-Catalyst-Tests-Model-Universe-Core'
}

{ #category : #'as yet unclassified' }
BVCCelestialObjectTests >> setUp [
	super setUp
]

{ #category : #'as yet unclassified' }
BVCCelestialObjectTests >> tearDown [
	super tearDown
]

{ #category : #'as yet unclassified' }
BVCCelestialObjectTests >> testAttributes [

  | celestialObject parent |
  celestialObject := BVCCelestialObject
  	withParent: ( parent := BVCCelestialObject new ).

  self assert: ( celestialObject identifier isKindOf: UUID ).
  self assert: ( celestialObject seed isKindOf: Integer ).
  self assert: celestialObject title isNil.
  self assert: celestialObject comment isNil.
  self assert: celestialObject parent isNil.
  celestialObject
    title: 'Test Title';
    comment: 'Test Comment';
    parent: parent.
  self assert: celestialObject title = 'Test Title'.
  self assert: celestialObject comment = 'Test Comment'.
  self assert: celestialObject parent == parent
]
