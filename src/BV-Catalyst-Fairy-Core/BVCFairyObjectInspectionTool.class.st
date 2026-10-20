"
Barry-local adapter to bounded primitive metadata over existing GT chat object storages. Available to Barry and Explorer without evaluation or process-control capabilities.
"
Class {
	#name : 'BVCFairyObjectInspectionTool',
	#superclass : 'GtLAbstractMagritteFunctionTool',
	#instVars : [
		'rootChat'
	],
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyObjectInspectionTool >> description [
	^ 'Bounded live inspection of Catalyst chats and their retained child objects. Empty ownerId/objectId lists accessible image-local owners and a bounded index. Use the returned ownerId with objectId to resolve the correct storage across chats. Optional slotPath follows up to three named non-sensitive fields. Returns primitive metadata only: no evaluation, selector invocation, process control, credentials, application printing or custom views. Missing owners do not establish cessation.'
]

{ #category : 'accessing' }
BVCFairyObjectInspectionTool >> name [
	^ 'inspectLiveObject'
]

{ #category : 'magritte' }
BVCFairyObjectInspectionTool >> objectIdDescription [
	<magritteDescription>
	^ MAStringDescription new label: 'Object id'; accessor: #objectId; beOptional
]

{ #category : 'magritte' }
BVCFairyObjectInspectionTool >> ownerIdDescription [
	<magritteDescription>
	^ MAStringDescription new label: 'Owner id'; accessor: #ownerId; beOptional
]

{ #category : 'private' }
BVCFairyObjectInspectionTool >> privatePerformToolCall: aToolCall inContext: aContext [
	| root arguments |
	root := rootChat ifNil: [ aContext currentChat ].
	(root isKindOf: BVCFairyChat) ifFalse: [
		^ GtLProblemDomainObject new description: 'Live inspection requires a Catalyst chat owner.' ].
	arguments := aToolCall arguments.
	^ [ BVCFairyObjectInspection new
		inspectOwner: (arguments at: 'ownerId' ifAbsent: [ '' ])
		object: (arguments at: 'objectId' ifAbsent: [ '' ])
		path: (arguments at: 'slotPath' ifAbsent: [ '' ])
		from: root ] on: Error do: [ :error |
		BVCFairyObjectInspection new unavailableBecause: error class name ]
]

{ #category : 'accessing' }
BVCFairyObjectInspectionTool >> rootChat [
	^ rootChat
]

{ #category : 'accessing' }
BVCFairyObjectInspectionTool >> rootChat: aChat [
	rootChat := aChat
]

{ #category : 'magritte' }
BVCFairyObjectInspectionTool >> slotPathDescription [
	<magritteDescription>
	^ MAStringDescription new label: 'Slot path'; accessor: #slotPath; beOptional
]
