Class {
	#name : #BVCAIAbstractElement,
	#superclass : #BlElement,
	#traits : 'TBrLayoutResizable',
	#classTraits : 'TBrLayoutResizable classTrait',
	#instVars : [
		'navigationModel'
	],
	#category : #'BV-Catalyst-Fairy-Core-Basic'
}

{ #category : #'private - asserting' }
BVCAIAbstractElement >> assertNavigationModel: aBVCAINavigationModel [
	self 
		assert: [ aBVCAINavigationModel isNotNil ] 
		description: [ 'Navigation model must be non-nil' ].
	self 
		assert: [ aBVCAINavigationModel ~= BVCAINavigationModel null ] 
		description: [ 'Navigation model must be different from ', BVCAINavigationModel null className ].
	
]

{ #category : #defaults }
BVCAIAbstractElement >> defaultNavigationModel [
	^ BVCAINavigationModel null
]

{ #category : #initialization }
BVCAIAbstractElement >> initialize [
	super initialize.
	self matchParent.
	navigationModel := self defaultNavigationModel.
	self initializeListeners
]

{ #category : #initialization }
BVCAIAbstractElement >> initializeListeners [
	self
		when: GtCoderToReplace
		do: [ :anEvent | self replaceFrom: anEvent ].

	self
		when: GtCoderToSpawn
		do: [ :anEvent | self spawnFrom: anEvent ].
		
	self
		when: GtCoderToSpawnInSpace
		do: [ :anEvent | self spawnInSpaceFrom: anEvent ].
]

{ #category : #'api - accessing' }
BVCAIAbstractElement >> navigationModel [
	<return: #GtCoderNavigationModel>
	^ navigationModel
]

{ #category : #'api - accessing' }
BVCAIAbstractElement >> navigationModel: aGtCoderNavigationModel [
	navigationModel = aGtCoderNavigationModel ifTrue: [  ^ self ].
	self unsubscribeFromNavigationModel.
	navigationModel := aGtCoderNavigationModel.
	self subscribeToNavigationModel.
	self onNavigationModelChanged.
]

{ #category : #'private - hooks' }
BVCAIAbstractElement >> onNavigationModelChanged [
	"Subclasses can react to navigation model changes."
]

{ #category : #'api - updating' }
BVCAIAbstractElement >> pushCoder: aCoderOrCoders [
	self navigationModel selectCoder: aCoderOrCoders
]

{ #category : #'private - event handling' }
BVCAIAbstractElement >> replaceFrom: aGtCoderToReplaceEvent [
	aGtCoderToReplaceEvent consumed: true.
	
	self pushCoder: aGtCoderToReplaceEvent coder
]

{ #category : #'private - event handling' }
BVCAIAbstractElement >> spawnFrom: aGtCoderToSpawnEvent [
	aGtCoderToSpawnEvent consumed: true.
	
	self phlow spawnTool: (GtReadyCoderTool coder: (aGtCoderToSpawnEvent coder))
]

{ #category : #'private - event handling' }
BVCAIAbstractElement >> spawnInSpaceFrom: aGtCoderToSpawnInSpaceEvent [
	aGtCoderToSpawnInSpaceEvent consumed: true.
]

{ #category : #'private - subscriptions' }
BVCAIAbstractElement >> subscribeToNavigationModel [
	"Subclasses can subscribe to the navigation model"
]

{ #category : #'private - subscriptions' }
BVCAIAbstractElement >> unsubscribeFromNavigationModel [
	self navigationModel = GtCoderNavigationModel null ifTrue: [ ^ self ].
	self navigationModel unsubscribe: self.
]
