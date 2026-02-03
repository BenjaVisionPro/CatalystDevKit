Class {
	#name : 'CRRuntimeServiceConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'displayName',
		'serviceClass',
		'configuration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> configuration [
	^ configuration
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> configuration: anObject [
	configuration := anObject
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> displayName: anObject [
	displayName := anObject
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> identifier [
	^ identifier
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> identifier: anObject [
	identifier := anObject
]

{ #category : 'initialization' }
CRRuntimeServiceConfiguration >> initialize [
	super initialize.
	identifier := nil.
	displayName := ''.
	serviceClass := nil.
	configuration := nil
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> serviceClass [
	^ serviceClass
]

{ #category : 'accessing' }
CRRuntimeServiceConfiguration >> serviceClass: anObject [
	serviceClass := anObject
]

{ #category : 'validation' }
CRRuntimeServiceConfiguration >> validateOn: result [
	| serviceLabel |
	serviceLabel := identifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ identifier printString ].

	identifier isNil
		ifTrue: [ result addError: 'Service identifier is required.' ]
		ifFalse: [ identifier isSymbol
				ifFalse: [ result
						addError: 'Service identifier must be a Symbol; got ' , identifier printString , ' ('
								, identifier class name , ').' ] ].

	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result addError: 'Service ' , serviceLabel , ' displayName is required.' ].

	serviceClass isNil
		ifTrue: [ result addError: 'Service ' , serviceLabel , ' serviceClass is required.' ]
		ifFalse: [ serviceClass isClass
				ifFalse: [ result
						addError: 'Service ' , serviceLabel , ' serviceClass must be a Class; got '
								, serviceClass printString , ' (' , serviceClass class name , ').' ]
				ifTrue: [ (serviceClass inheritsFrom: CRWorkerService)
						ifFalse: [ result
								addError: 'Service ' , serviceLabel , ' serviceClass ' , serviceClass name
										, ' must inherit from CRWorkerService.' ] ] ]
]
