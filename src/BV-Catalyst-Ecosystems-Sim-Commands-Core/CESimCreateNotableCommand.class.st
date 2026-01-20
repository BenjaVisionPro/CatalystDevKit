Class {
	#name : 'CESimCreateNotableCommand',
	#superclass : 'CESimToolLifecycleCommand',
	#instVars : [
		'definitionKey',
		'transform',
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimCreateNotableCommand class >> withDefinitionKey: aKey transform: aTransform state: aState [
  ^ self new
    definitionKey: aKey;
    transform: aTransform;
    state: aState;
    yourself
]

{ #category : 'contributing' }
CESimCreateNotableCommand >> contributeToLifecycleBehaviourModule: aModule intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aModule
		applyCreateNotableCommand: self
		intoUpdate: aCESimUpdate
		inContext: aCESimRunContext
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> definitionKey [
	^ definitionKey
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> definitionKey: aKey [
	definitionKey := aKey
]

{ #category : 'producing' }
CESimCreateNotableCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #createNotableRequested;
		at: #definitionKey put: definitionKey;
		at: #transform put: transform;
		at: #state put: state;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> state [
	^ state
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> state: aState [
	state := aState
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> transform: aTransform [
	transform := aTransform
]
