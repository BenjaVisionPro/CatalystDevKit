Class {
	#name : 'CRServiceDeploymentConfiguration',
	#superclass : 'Object',
	#instVars : [
		'serviceIdentifier',
		'displayName',
		'targetHostTags',
		'initialCount',
		'scaleConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> displayName: anObject [
	displayName := anObject
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> initialCount [
	^ initialCount
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> initialCount: anObject [
	initialCount := anObject
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> scaleConfiguration [
	^ scaleConfiguration
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> scaleConfiguration: anObject [
	scaleConfiguration := anObject
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> serviceIdentifier [
	^ serviceIdentifier
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> serviceIdentifier: anObject [
	serviceIdentifier := anObject
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> targetHostTags [
	^ targetHostTags
]

{ #category : 'accessing' }
CRServiceDeploymentConfiguration >> targetHostTags: anObject [
	targetHostTags := anObject
]

{ #category : 'validation' }
CRServiceDeploymentConfiguration >> validateOn: result knownServiceIdentifiers: knownServiceIds [
	| depLabel |
	depLabel := serviceIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ serviceIdentifier printString ].

	serviceIdentifier isNil
		ifTrue: [ result addError: 'Service deployment serviceIdentifier is required.' ]
		ifFalse: [ serviceIdentifier isSymbol
				ifFalse: [ result
						addError: 'Service deployment serviceIdentifier must be a Symbol; got '
								, serviceIdentifier printString , ' (' , serviceIdentifier class name
								, ').' ]
				ifTrue: [ (knownServiceIds includes: serviceIdentifier)
						ifFalse: [ result
								addError: 'Service deployment references unknown service ' , serviceIdentifier printString
										, '.' ] ] ].

	(displayName isNil or: [ displayName asString isEmpty ])
		ifTrue: [ result
				addError: 'Service deployment ' , depLabel , ' displayName is required.' ].

	(targetHostTags isNil or: [ targetHostTags isCollection not ])
		ifTrue: [ ^ result
				addError: 'Service deployment ' , depLabel
						, ' targetHostTags must be a collection of Symbols.' ].

	targetHostTags isEmpty
		ifTrue: [ result
				addError: 'Service deployment ' , depLabel , ' must specify at least one targetHostTag.' ].

	(targetHostTags allSatisfy: [ :each | each isSymbol ])
		ifFalse: [ result
				addError: 'Service deployment ' , depLabel , ' targetHostTags must be Symbols; got '
						, targetHostTags printString , '.' ].

	(initialCount isInteger and: [ initialCount >= 0 ])
		ifFalse: [ result
				addError: 'Service deployment ' , depLabel
						, ' initialCount must be a non-negative Integer; got '
						, initialCount printString , '.' ].

	(serviceIdentifier isSymbol and: [ scaleConfiguration notNil ])
		ifTrue: [ scaleConfiguration validateOn: result forWorkerIdentifier: serviceIdentifier ]
]
