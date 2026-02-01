Class {
	#name : 'CRRuntimeConfiguration',
	#superclass : 'Object',
	#instVars : [
		'displayName',
		'version',
		'workers',
		'topology',
		'deployment'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRRuntimeConfiguration >> deployment [
	^ deployment
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> deployment: aCRRuntimeDeploymentConfiguration [
	deployment := aCRRuntimeDeploymentConfiguration
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> displayName [
	^ displayName
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> displayName: aString [
	displayName := aString 
]

{ #category : 'initialization' }
CRRuntimeConfiguration >> initialize [
	super initialize.
	displayName := 'Runtime'.
	version := nil.
	workers := OrderedCollection new.
	topology := nil.
	deployment := nil
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> topology [
	^ topology
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> topology: aCRTopologyConfiguration [
	topology := aCRTopologyConfiguration
]

{ #category : 'validation' }
CRRuntimeConfiguration >> validate [
	^ CRRuntimeConfigurationValidator new validate: self
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> version [
	^ version
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> version: anObject [
	version := anObject
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> workerConfigurationNamed: anIdentifierString [
	^ workers
		detect: [ :each | each identifier = anIdentifierString asString ]
		ifNone: [ nil ]
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> workerIdentifiers [
	^ workers collect: #identifier
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> workers [
	^ workers
]

{ #category : 'accessing' }
CRRuntimeConfiguration >> workers: aCollection [
	workers := aCollection asOrderedCollection
]
