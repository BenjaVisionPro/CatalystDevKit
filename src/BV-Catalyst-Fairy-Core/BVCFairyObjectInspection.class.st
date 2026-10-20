"
A live, bounded metadata observation with explicit image-local storage ownership. Does not retain inspected objects or invoke their printers, accessors or custom views. Strings and sensitive fields are opaque. Missing references are not cessation evidence.
"
Class {
	#name : 'BVCFairyObjectInspection',
	#superclass : 'Object',
	#instVars : [
		'data'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'private' }
BVCFairyObjectInspection >> basicClassOf: anObject [
	^ (Object lookupSelector: #class) valueWithReceiver: anObject arguments: #()
]

{ #category : 'private' }
BVCFairyObjectInspection >> basicSizeOf: anObject [
	^ (Object lookupSelector: #basicSize) valueWithReceiver: anObject arguments: #()
]

{ #category : 'private' }
BVCFairyObjectInspection >> basicSlotAt: index of: anObject [
	^ (Object lookupSelector: #instVarAt:) valueWithReceiver: anObject arguments: { index }
]

{ #category : 'accessing' }
BVCFairyObjectInspection >> data [
	^ data
]

{ #category : 'private' }
BVCFairyObjectInspection >> framesFor: aContext limit: limit [
	| context frames |
	context := aContext.
	frames := OrderedCollection new.
	[ context notNil and: [ frames size < limit ] ] whileTrue: [
		frames add: { 'class' -> context method methodClass name.
			'selector' -> context method selector asString } asDictionary.
		context := context sender ].
	^ frames asArray
]

{ #category : 'inspection' }
BVCFairyObjectInspection >> inspectOwner: ownerId object: objectId path: slotPath from: root [
	| owners owner object names index parts |
	{ ownerId. objectId. slotPath } do: [ :value |
		(value isNil or: [ value isString and: [ value size <= 256 ] ]) ifFalse: [
			data := { 'status' -> 'invalidReference' } asDictionary. ^ self ] ].
	owners := self ownersFrom: root.
	owner := (ownerId isNil or: [ ownerId isEmpty ])
		ifTrue: [ owners first ]
		ifFalse: [ owners detect: [ :each | each key = ownerId ] ifNone: [ nil ] ].
	data := { 'observedAt' -> DateAndTime now asString.
		'observation' -> 'live metadata snapshot; not durable execution state'.
		'limits' -> '16 roots, 64 owners, 1024 indexed references per root; 20 index entries, 12 fields/items, 3 path segments; strings show lengths only' } asDictionary.
	owner ifNil: [
		data at: 'status' put: 'ownerUnavailable';
			at: 'reason' put: 'Owner is outside accessible live owners or has expired. Missing references do not establish cessation.'.
		^ self ].
	data at: 'ownerId' put: owner key.
	(objectId isNil or: [ objectId isEmpty ]) ifTrue: [
		data at: 'status' put: 'index';
			at: 'owners' put: (owners collect: [ :each |
				{ 'ownerId' -> each key. 'class' -> each value class name.
				  'state' -> each value state class name } asDictionary ]) asArray;
			at: 'objects' put: ((owner value objectStorage objectIds first: (owner value objectStorage objectIds size min: 20))
				collect: [ :id | { 'objectId' -> id asString.
					'class' -> (self basicClassOf: (owner value objectStorage objectAt: id)) name } asDictionary ]) asArray;
			at: 'objectCount' put: owner value objectStorage objectIds size.
		^ self ].
	object := [ owner value objectStorage objectAt: objectId
		ifPresent: [ :value | value ]
		ifAbsent: [ data at: 'status' put: 'objectMissing'. ^ self ] ]
		on: Error do: [ :error | data at: 'status' put: 'invalidReference'. ^ self ].
	parts := (slotPath ifNil: [ '' ]) findTokens: '/'.
	parts size > 3 ifTrue: [ data at: 'status' put: 'pathLimitExceeded'. ^ self ].
	parts do: [ :part |
		((self sensitiveName: part) or: [ self opaqueClass: (self basicClassOf: object) ]) ifTrue: [
			data at: 'status' put: 'accessDenied'. ^ self ].
		names := (self basicClassOf: object) allInstVarNames.
		index := names indexOf: part asSymbol ifAbsent: [ 0 ].
		index = 0 ifTrue: [ data at: 'status' put: 'slotMissing'. ^ self ].
		object := self basicSlotAt: index of: object ].
	data at: 'status' put: 'observed'; at: 'objectId' put: objectId;
		at: 'snapshot' put: (self snapshotOf: object).
	^ self
]

{ #category : 'views' }
BVCFairyObjectInspection >> llmRawDataViewFor: aView [
	<gtLlmDataView>
	^ aView jsonData: [ data ]
]

{ #category : 'private' }
BVCFairyObjectInspection >> opaqueClass: aClass [
	^ (aClass inheritsFrom: Behavior)
		or: [ #('Client' 'Credential' 'Socket' 'Stream' 'Context' 'BlockClosure' 'Process')
			anySatisfy: [ :word | aClass name includesSubstring: word ] ]
]

{ #category : 'private' }
BVCFairyObjectInspection >> ownersFrom: aRoot [
	| roots owners |
	roots := OrderedCollection with: aRoot.
	(GtLChatRegistry current chats select: [ :each | each isKindOf: BVCFairyChat ]) do: [ :each |
		(roots includes: each) ifFalse: [ roots add: each ] ].
	owners := OrderedCollection new.
	(roots first: (roots size min: 16)) do: [ :root |
		owners add: root inspectionId -> root.
		(root objectStorage objectIds first: (root objectStorage objectIds size min: 1024)) do: [ :id |
			| object |
			object := root objectStorage objectAt: id.
			(((self basicClassOf: object) = BVCFairyAgentExecution) and: [ owners size < 64 ]) ifTrue: [
				owners add: (root inspectionId, '/', id asString) -> object agent ] ] ].
	^ owners
]

{ #category : 'private' }
BVCFairyObjectInspection >> sensitiveName: aString [
	| lower |
	lower := aString asLowercase.
	^ #('password' 'secret' 'credential' 'token' 'auth' 'header' 'client' 'connection' 'socket' 'stream' 'key' 'receiver' 'sender' 'environment' 'globals')
		anySatisfy: [ :word | lower includesSubstring: word ]
]

{ #category : 'private' }
BVCFairyObjectInspection >> snapshotOf: anObject [
	| type summary names slots |
	type := self basicClassOf: anObject.
	summary := self valueSummary: anObject.
	type = Process ifTrue: [
		summary at: 'terminated' put: anObject isTerminated;
			at: 'frames' put: (self framesFor: anObject suspendedContext limit: 12).
		^ summary ].
	type = Context ifTrue: [
		summary at: 'frames' put: (self framesFor: anObject limit: 12).
		^ summary ].
	(self opaqueClass: type) ifTrue: [ summary at: 'opaque' put: true. ^ summary ].
	(type = BVCFairyAgentExecution) ifTrue: [
		summary at: 'executionId' put: anObject executionId;
			at: 'role' put: anObject initialRequest agentName;
			at: 'state' put: anObject agent state class name;
			at: 'responseClass' put: (self basicClassOf: anObject responseMessage) name;
			at: 'workers' put: (self workersFor: anObject);
			at: 'pendingUI' put: ((BVCFairyUIRequest pending select: [ :request | request chat == anObject agent ])
				collect: [ :request | request state asString ]) asArray ].
	names := type allInstVarNames.
	slots := (1 to: (names size min: 12)) collect: [ :slotIndex |
		{ 'name' -> (names at: slotIndex) asString.
			'summary' -> ((self sensitiveName: (names at: slotIndex) asString)
				ifTrue: [ { 'redacted' -> true } asDictionary ]
				ifFalse: [ self valueSummary: (self basicSlotAt: slotIndex of: anObject) ]) } asDictionary ].
	summary at: 'fields' put: slots asArray; at: 'fieldCount' put: names size.
	type = Array ifTrue: [
		summary at: 'items' put: ((1 to: ((self basicSizeOf: anObject) min: 12)) collect: [ :index |
			self valueSummary: ((Object lookupSelector: #basicAt:) valueWithReceiver: anObject arguments: { index }) ]) asArray ].
	^ summary
]

{ #category : 'inspection' }
BVCFairyObjectInspection >> unavailableBecause: exceptionClass [
	data := { 'status' -> 'observationUnavailable'.
		'errorClass' -> exceptionClass.
		'reason' -> 'Concurrent or unsupported live state prevented this bounded observation. It is not evidence of cessation; retry read-only inspection after identifying the reference.' } asDictionary.
	^ self
]

{ #category : 'private' }
BVCFairyObjectInspection >> valueSummary: anObject [
	| type summary |
	type := self basicClassOf: anObject.
	summary := { 'class' -> type name } asDictionary.
	(type = UndefinedObject or: [ type = True or: [ type = False ] ]) ifTrue: [
		summary at: 'value' put: anObject. ^ summary ].
	type = SmallInteger ifTrue: [ summary at: 'value' put: anObject. ^ summary ].
	(type = ByteString or: [ type = WideString or: [ type = ByteArray or: [ type = Array ] ] ]) ifTrue: [
		summary at: 'length' put: (self basicSizeOf: anObject) ].
	^ summary
]

{ #category : 'private' }
BVCFairyObjectInspection >> workersFor: anExecution [
	| processes matches truncated |
	processes := Process allInstances select: [ :process | process isTerminated not and: [ process suspendedContext notNil ] ].
	matches := OrderedCollection new.
	truncated := processes size > 256.
	(processes first: (processes size min: 256)) do: [ :process |
		| context count found |
		context := process suspendedContext.
		count := 0.
		found := false.
		[ context notNil and: [ count < 100 ] ] whileTrue: [
			(context receiver == anExecution or: [ context receiver == anExecution agent or: [
				context receiver == anExecution agent provider ] ]) ifTrue: [ found := true ].
			count := count + 1.
			context := context sender ].
		context ifNotNil: [ truncated := true ].
		found ifTrue: [
			matches size < 8
				ifTrue: [ matches add: { 'frames' -> (self framesFor: process suspendedContext limit: 12) } asDictionary ]
				ifFalse: [ truncated := true ] ] ].
	^ { 'matches' -> matches asArray. 'scanTruncated' -> truncated.
		'cessation' -> 'Not established by a bounded snapshot alone.' } asDictionary
]
