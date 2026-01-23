Class {
	#name : 'CESimAddEntityCommand',
	#superclass : 'CESimExternalCommand',
	#instVars : [
		'definitionKey',
		'transform',
		'state'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Commands-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
}

{ #category : 'instance creation' }
CESimAddEntityCommand class >> withDefinitionKey: aKey transform: aTransform state: aState [
  ^ self new
    definitionKey: aKey;
    transform: aTransform;
    state: aState;
    yourself
]

{ #category : 'contributing' }
CESimAddEntityCommand >> contributeLifecycleIntoUpdate: aSimUpdate inContext: aSimContext [
	aSimUpdate
		addEntityOp: (CESimAddEntityToRegionOp
				withRegionId: aSimContext subject homeRegionId
				entity: (aSimContext
						newEntityWithDefinitionKey: definitionKey
						transform: transform
						state: state))
]

{ #category : 'accessing' }
CESimAddEntityCommand >> definitionKey [
	^ definitionKey
]

{ #category : 'accessing' }
CESimAddEntityCommand >> definitionKey: aKey [
	definitionKey := aKey
]

{ #category : 'producing' }
CESimAddEntityCommand >> produceEventsIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
	aCESimUpdate addEvent: (Dictionary new
		at: #type put: #createNotableRequested;
		at: #definitionKey put: definitionKey;
		at: #transform put: transform;
		at: #state put: state;
		at: #tickId put: aCESimRunContext tickId;
		yourself)
]

{ #category : 'accessing' }
CESimAddEntityCommand >> state [
	^ state
]

{ #category : 'accessing' }
CESimAddEntityCommand >> state: aState [
	state := aState
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform [
	^ transform
]

{ #category : 'accessing' }
CESimAddEntityCommand >> transform: aTransform [
	transform := aTransform
]
