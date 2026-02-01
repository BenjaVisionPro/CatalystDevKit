Class {
	#name : 'CRTopologyConfiguration',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'hosts',
		'placementStrategyConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRTopologyConfiguration >> displayName [ ^ displayName ]
{ #category : 'accessing' }
CRTopologyConfiguration >> displayName: aString [ displayName := aString asString ]

{ #category : 'initialization' }
CRTopologyConfiguration >> initialize [
	super initialize.
	displayName := 'Topology'.
	hosts := OrderedCollection new.
	placementStrategyConfiguration := nil
]

{ #category : 'accessing' }
CRTopologyConfiguration >> hosts [ ^ hosts ]
{ #category : 'accessing' }
CRTopologyConfiguration >> hosts: aCollection [ hosts := aCollection asOrderedCollection ]

{ #category : 'accessing' }
CRTopologyConfiguration >> hostConfigurationNamed: aHostIdentifier [
	^ hosts detect: [ :each | each identifier = aHostIdentifier asString ] ifNone: [ nil ]
]

{ #category : 'accessing' }
CRTopologyConfiguration >> placementStrategyConfiguration [ ^ placementStrategyConfiguration ]
{ #category : 'accessing' }
CRTopologyConfiguration >> placementStrategyConfiguration: aCRPlacementStrategyConfiguration [ placementStrategyConfiguration := aCRPlacementStrategyConfiguration ]

{ #category : 'validation' }
CRTopologyConfiguration >> validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers [
	| hostIds |
	hostIds := Set new.
	hosts do: [ :each |
		each validateOn: aValidationResult knownWorkerIdentifiers: knownWorkerIdentifiers.
		(each identifier isEmpty) ifFalse: [
			(hostIds includes: each identifier)
				ifTrue: [ aValidationResult addError: 'Duplicate host identifier ', each identifier printString, '.' ]
				ifFalse: [ hostIds add: each identifier ] ] ].
	placementStrategyConfiguration ifNil: [ aValidationResult addError: 'Topology must specify a placement strategy configuration.' ].
]
