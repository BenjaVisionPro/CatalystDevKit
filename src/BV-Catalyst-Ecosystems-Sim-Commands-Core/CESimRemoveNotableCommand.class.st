Class {
	#name : 'CESimRemoveNotableCommand',
	#superclass : 'CESimToolLifecycleCommand',
	#instVars : [
		'entityId'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimRemoveNotableCommand class >> entityId: aCEEntityId [
	^ self new
		entityId: aCEEntityId;
		yourself
]

{ #category : 'contributing' }
CESimRemoveNotableCommand >> contributeToLifecycleBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aModule
		applyRemoveNotableCommand: self
		intoUpdate: aCESimUpdate
		inContext: aCESimRunContext
]

{ #category : 'accessing' }
CESimRemoveNotableCommand >> entityId [
	^ entityId
]

{ #category : 'accessing' }
CESimRemoveNotableCommand >> entityId: aCEEntityId [
	entityId := aCEEntityId
]

{ #category : 'producing' }
CESimRemoveNotableCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	"Events only."
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #removeNotableRequested;
		at: #entityId put: entityId;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]
