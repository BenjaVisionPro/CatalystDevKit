Class {
	#name : 'CRRuntimeConfigurationValidator',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'validation' }
CRRuntimeConfigurationValidator >> validate: aCRRuntimeConfiguration [
	| result workerIds serviceIds |
	result := CRRuntimeConfigurationValidationResult new.

	(aCRRuntimeConfiguration displayName isNil
		or: [ aCRRuntimeConfiguration displayName asString isEmpty ])
		ifTrue: [ result addError: 'Runtime configuration displayName is required.' ].

	workerIds := Set new.
	(aCRRuntimeConfiguration workers ifNil: [ #() ])
		do: [ :each | 
			each validateOn: result.
			each identifier isNil
				ifFalse: [ (workerIds includes: each identifier)
						ifTrue: [ result
								addError: 'Duplicate worker identifier ' , each identifier printString , '.' ]
						ifFalse: [ workerIds add: each identifier ] ] ].

	serviceIds := Set new.
	(aCRRuntimeConfiguration services ifNil: [ #() ])
		do: [ :each | 
			each validateOn: result.
			each identifier isNil
				ifFalse: [ (serviceIds includes: each identifier)
						ifTrue: [ result
								addError: 'Duplicate service identifier ' , each identifier printString , '.' ]
						ifFalse: [ serviceIds add: each identifier ] ] ].

	aCRRuntimeConfiguration topology
		ifNil: [ result addError: 'Runtime configuration must specify topology.' ]
		ifNotNil: [ aCRRuntimeConfiguration topology
				validateOn: result
				knownWorkerIdentifiers: workerIds
				knownServiceIdentifiers: serviceIds ].

	aCRRuntimeConfiguration deployment
		ifNil: [ result addError: 'Runtime configuration must specify deployment.' ]
		ifNotNil: [ aCRRuntimeConfiguration deployment
				validateOn: result
				knownServiceIdentifiers: serviceIds ].

	^ result
]
