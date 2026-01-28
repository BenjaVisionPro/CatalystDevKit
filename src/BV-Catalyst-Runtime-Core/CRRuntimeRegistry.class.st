Class {
	#name : 'CRRuntimeRegistry',
	#superclass : 'Object',
	#instVars : [
		'runtimes'
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
	runtimes := OrderedCollection new
]

{ #category : 'registry' }
CRRuntimeRegistry >> register: aRuntime [
	"I remember a runtime so it can be discovered and shut down later."

	runtimes add: aRuntime
]

{ #category : 'accessing' }
CRRuntimeRegistry >> runtimes [
	^ runtimes
]

{ #category : 'registry' }
CRRuntimeRegistry >> unregister: aRuntime [
	"I forget a runtime when it is shut down."

	runtimes remove: aRuntime ifAbsent: [  ]
]
