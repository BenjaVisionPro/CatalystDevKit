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
CRTopologyConfiguration >> displayName [ ^ displayName
]

{ #category : 'accessing' }
CRTopologyConfiguration >> displayName: aString [
	displayName := aString
]

{ #category : 'accessing' }
CRTopologyConfiguration >> hostConfigurationNamed: aHostIdentifier [
	^ hosts detect: [ :each | each identifier = aHostIdentifier ] ifNone: [ nil ]
]

{ #category : 'accessing' }
CRTopologyConfiguration >> hosts [ ^ hosts
]

{ #category : 'accessing' }
CRTopologyConfiguration >> hosts: aCollection [ hosts := aCollection asOrderedCollection
]

{ #category : 'initialization' }
CRTopologyConfiguration >> initialize [
	super initialize.
	displayName := 'Topology'.
	hosts := OrderedCollection new.
	placementStrategyConfiguration := nil
]

{ #category : 'accessing' }
CRTopologyConfiguration >> placementStrategyConfiguration [ ^ placementStrategyConfiguration
]

{ #category : 'accessing' }
CRTopologyConfiguration >> placementStrategyConfiguration: aCRPlacementStrategyConfiguration [ placementStrategyConfiguration := aCRPlacementStrategyConfiguration
]

{ #category : 'validation' }
CRTopologyConfiguration >> validateOn: result knownWorkerIdentifiers: knownWorkerIds [
	| hostIds |
	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Topology configuration displayName is required.' ].

	hosts
		ifNil: [ ^ result addError: 'Topology configuration must specify hosts.' ].
	hosts isEmpty
		ifTrue: [ result addError: 'Topology configuration must specify at least one host.' ].

	hostIds := Set new.
	hosts
		do: [ :each | 
			each validateOn: result knownWorkerIdentifiers: knownWorkerIds.
			each identifier isNil
				ifFalse: [ (hostIds includes: each identifier)
						ifTrue: [ result
								addError: 'Duplicate host identifier ' , each identifier printString , '.' ]
						ifFalse: [ hostIds add: each identifier ] ] ].

	placementStrategyConfiguration
		ifNil: [ result addError: 'Topology configuration must specify placement strategy.' ]
]

{ #category : 'validation' }
CRTopologyConfiguration >> validateOn: result knownWorkerIdentifiers: knownWorkerIds knownServiceIdentifiers: knownServiceIds [
	| hostIds |
	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Topology configuration displayName is required.' ].

	hosts
		ifNil: [ ^ result addError: 'Topology configuration must specify hosts.' ].
	hosts isEmpty
		ifTrue: [ result addError: 'Topology configuration must specify at least one host.' ].

	hostIds := Set new.
	hosts
		do: [ :each | 
			each
				validateOn: result
				knownWorkerIdentifiers: knownWorkerIds
				knownServiceIdentifiers: knownServiceIds.
			each identifier isNil
				ifFalse: [ (hostIds includes: each identifier)
						ifTrue: [ result
								addError: 'Duplicate host identifier ' , each identifier printString , '.' ]
						ifFalse: [ hostIds add: each identifier ] ] ].

	placementStrategyConfiguration
		ifNil: [ result addError: 'Topology configuration must specify placement strategy.' ]
]
