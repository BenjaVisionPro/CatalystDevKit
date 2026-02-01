Class {
	#name : 'CRRuntimeConfigurationValidator',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'validation' }
CRRuntimeConfigurationValidator >> validate: aCRRuntimeConfiguration [
	| result ids |
	result := CRRuntimeConfigurationValidationResult new.

	(aCRRuntimeConfiguration displayName isNil or: [ aCRRuntimeConfiguration displayName asString isEmpty ])
		ifTrue: [ result addError: 'Runtime configuration displayName is required.' ].

	ids := Set new.
	aCRRuntimeConfiguration workers do: [ :each |
		each validateOn: result.
		(each identifier isEmpty) ifFalse: [
			(ids includes: each identifier)
				ifTrue: [ result addError: 'Duplicate worker identifier ', each identifier printString, '.' ]
				ifFalse: [ ids add: each identifier ] ] ].

	aCRRuntimeConfiguration topology
		ifNil: [ result addError: 'Runtime configuration must specify topology.' ]
		ifNotNil: [ aCRRuntimeConfiguration topology validateOn: result knownWorkerIdentifiers: ids ].

	aCRRuntimeConfiguration deployment
		ifNil: [ result addError: 'Runtime configuration must specify deployment.' ]
		ifNotNil: [ aCRRuntimeConfiguration deployment validateOn: result knownWorkerIdentifiers: ids ].

	^ result
]
