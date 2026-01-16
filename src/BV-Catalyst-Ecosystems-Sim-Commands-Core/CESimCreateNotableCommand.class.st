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

{ #category : 'accessing' }
CESimCreateNotableCommand >> definitionKey: aKey [
	definitionKey := aKey
]

{ #category : 'producing' }
CESimCreateNotableCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  | regionId notable |
  regionId := aCESimRunContext subject homeRegionId.

  "Uses your existing context factory (constructs notable; IDs remain hidden)."
  notable := aCESimRunContext
    newNotableWithDefinitionKey: definitionKey
    transform: transform
    state: state.

  aCESimUpdate addEntityOp: (CESimAddNotableToRegionOp withRegionId: regionId notable: notable).
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> state: aState [
	state := aState
]

{ #category : 'accessing' }
CESimCreateNotableCommand >> transform: aTransform [
	transform := aTransform
]
