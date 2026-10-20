"
Controlled application hooks that count accidental printing or accessor execution during inspection.
"
Class {
	#name : 'BVCFairyInspectionProbe',
	#superclass : 'Object',
	#instVars : [
		'accesses',
		'value',
		'password'
	],
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'accessing' }
BVCFairyInspectionProbe >> accesses [
	^ accesses
]

{ #category : 'initialization' }
BVCFairyInspectionProbe >> initialize [
	super initialize.
	accesses := 0.
	value := 42.
	password := 'DO-NOT-EXPOSE-THIS-SECRET'
]

{ #category : 'accessing' }
BVCFairyInspectionProbe >> instVarAt: index [
	accesses := accesses + 1.
	^ super instVarAt: index
]

{ #category : 'printing' }
BVCFairyInspectionProbe >> printOn: aStream [
	accesses := accesses + 1.
	aStream nextPutAll: 'Application printer must not be used'
]

{ #category : 'accessing' }
BVCFairyInspectionProbe >> readSlotNamed: aName [
	accesses := accesses + 1.
	^ super readSlotNamed: aName
]

{ #category : 'accessing' }
BVCFairyInspectionProbe >> value [
	accesses := accesses + 1.
	^ value
]
