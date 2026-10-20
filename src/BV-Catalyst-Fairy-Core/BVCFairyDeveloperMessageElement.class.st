"
Barry developer bubble using the existing GT user message renderer and actions.
"
Class {
	#name : 'BVCFairyDeveloperMessageElement',
	#superclass : 'GtLUserMessageContentElement',
	#category : 'BV-Catalyst-Fairy-Core-UI',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'UI'
}

{ #category : 'instance creation' }
BVCFairyDeveloperMessageElement class >> newForChatList [
	^ self new margin: (BlInsets top: 5 bottom: 10 left: 80 right: 5)
]

{ #category : 'initialization' }
BVCFairyDeveloperMessageElement >> initialize [
	super initialize.
	headerElement addChildFirst: ((FontAwesomeIcons icon: #user) asElement size: 20 @ 20).
	self geometry: (BlRoundedRectangleGeometry cornerRadius: 12).
	self background: (Color gray alpha: 0.1).
	self padding: (BlInsets all: 10)
]
