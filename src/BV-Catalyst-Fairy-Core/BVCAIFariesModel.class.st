Class {
	#name : #BVCAIFariesModel,
	#superclass : #Object,
	#traits : 'TGtAnnouncer + TGtOptions',
	#classTraits : 'TGtAnnouncer classTrait + TGtOptions classTrait',
	#instVars : [
		'announcer',
		'items',
		'coders',
		'faries'
	],
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #'initialize-release' }
BVCAIFariesModel class >> forItems: aCollection [
	^ self new
		forItems: aCollection;
		yourself
]

{ #category : #'private - adding / removing' }
BVCAIFariesModel >> addFairy: aFairy [
	faries add: aFairy.
	self subscribeToFairy: aFairy.
	self notifyFairyAdded: aFairy.
]

{ #category : #'private - adding / removing' }
BVCAIFariesModel >> addFirstFairy: aFairy [
	coders addFirst: aFairy.
	self subscribeToFairy: aFairy.
	self notifyFairyAdded: aFairy
]

{ #category : #announcer }
BVCAIFariesModel >> announcer [
	^ announcer ifNil: [ announcer := Announcer new ]
]

{ #category : #testing }
BVCAIFariesModel >> canFilter [
	^ false
]

{ #category : #accessing }
BVCAIFariesModel >> faries [
	^ faries
]

{ #category : #'initialize-release' }
BVCAIFariesModel >> forItems: aCollection [
	items := aCollection.
	faries := items collect: [ :each | self newFairyFor: each ]
]

{ #category : #ui }
BVCAIFariesModel >> gtLiveFor: aView [
	<gtView>
	^ aView explicit 
		title: 'Live';
		priority: 10;
		stencil: [ self ]
]

{ #category : #'initialize-release' }
BVCAIFariesModel >> initialize [
	super initialize.
	faries := #().
	items := #()
]

{ #category : #private }
BVCAIFariesModel >> newCoderFor: anObject [
	self subclassResponsibility
]

{ #category : #'private - notifying' }
BVCAIFariesModel >> notifyFairyAdded: aFairy [
	self announce: (GtCodersCoderAdded new
		faries: self;
		fairy: aFairy)
]

{ #category : #'private - notifying' }
BVCAIFariesModel >> notifyFairyRemoved: aFairy [
	self announce: (GtCodersCoderRemoved new
		faries: self;
		fairy: aFairy)
]

{ #category : #'private - adding / removing' }
BVCAIFariesModel >> removeFairy: aFairy [
	self unsubscribeFromFairy: aFairy.
	faries remove: aFairy ifAbsent: [ ^ self ].
	self notifyFairyRemoved: aFairy
]

{ #category : #'private - subscriptions' }
BVCAIFariesModel >> subscribeToFairy: eachFairy [
]

{ #category : #'private - subscriptions' }
BVCAIFariesModel >> subscribeToSystem [
	"do nothing"
]

{ #category : #'private - subscriptions' }
BVCAIFariesModel >> unsubscribeFromFairy: aFairy [
	aFairy unsubscribe: self
]

{ #category : #'private - subscriptions' }
BVCAIFariesModel >> unsubscribeFromSystem [
	SystemAnnouncer uniqueInstance unsubscribe: self
]

{ #category : #updating }
BVCAIFariesModel >> updateFaries [
	| oldFaries |
	oldFaries := faries.
	faries := items collect: [ :each | self newFairyFor: each ].
	self
		announce:
			(GtCodersCodersChanged new
				faries: self;
				oldFaries: oldFaries;
				newFaries: faries;
				yourself)
]
