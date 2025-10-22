Class {
	#name : #BVCAIContentElement,
	#superclass : #BVCAIAbstractElement,
	#category : #'BV-Catalyst-Fairy-Core-Basic'
}

{ #category : #factory }
BVCAIContentElement class >> default [
	^ self new
		navigationModel: GtCoderNavigationModel default
]

{ #category : #initialization }
BVCAIContentElement >> initialize [
	super initialize.
	self layout: BlFrameLayout new
]

{ #category : #'hooks - children' }
BVCAIContentElement >> onAddedToSceneGraph [
	super onAddedToSceneGraph.
	self navigationModel subscribeToSystem.
]

{ #category : #'hooks - children' }
BVCAIContentElement >> onRemovedFromSceneGraph [
	super onRemovedFromSceneGraph.
	self navigationModel unsubscribeFromSystem.
]

{ #category : #'private - subscriptions' }
BVCAIContentElement >> subscribeToNavigationModel [
	super subscribeToNavigationModel.
	self navigationModel weak
		when: GtCoderNavigationCoderChanged send: #updateCoder: to: self.
]

{ #category : #'private - event handling' }
BVCAIContentElement >> updateCoder: anAnnouncement [
	self removeChildren.
	self
		addChild: (anAnnouncement coder asElement navigationModelForToolbar: self navigationModel)
]
