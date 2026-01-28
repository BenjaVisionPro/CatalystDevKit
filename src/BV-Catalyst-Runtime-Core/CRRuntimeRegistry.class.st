Class {
	#name : 'CRRuntimeRegistry',
	#superclass : 'Object',
	#instVars : [
		'runtimes',
		'announcer'
	],
	#classInstVars : [
		'Default'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'accessing' }
CRRuntimeRegistry class >> default [
	"I answer the shared registry used by GT/dev tooling."

	Default ifNil: [ Default := self new ].
	^ Default
]

{ #category : 'initialization' }
CRRuntimeRegistry >> initialize [
	super initialize.
	runtimes := OrderedCollection new.
	announcer := Announcer new
]

{ #category : 'registry' }
CRRuntimeRegistry >> register: aRuntime [
	"I remember a runtime so it can be discovered and stopped later."

	self runtimes add: aRuntime.
	announcer announce: (CRRuntimeRegistryChanged runtime: aRuntime)
]

{ #category : 'accessing' }
CRRuntimeRegistry >> runtimes [
	^ runtimes
]

{ #category : 'registry' }
CRRuntimeRegistry >> unregister: aRuntime [
	"I forget a runtime when it is stopped."

	(self runtimes remove: aRuntime ifAbsent: [ nil ])
		ifNotNil: [ announcer announce: (CRRuntimeRegistryChanged runtime: aRuntime) ]
]
