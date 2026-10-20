"
Barry-local chat presentation. Reuses GT message view models and renderer; keeps the existing draft composer outside the conversation list.
"
Class {
	#name : 'BVCFairyChatElement',
	#superclass : 'GtLChatElement',
	#instVars : [
		'composerElement'
	],
	#category : 'BV-Catalyst-Fairy-Core-UI',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'UI'
}

{ #category : 'initialization' }
BVCFairyChatElement >> initialize [
	super initialize.
	self layout: BlLinearLayout vertical.
	composerElement := GtLNewMessageElement new.
	self addChild: composerElement as: #catalystDraftComposer
]

{ #category : 'initialization' }
BVCFairyChatElement >> initializeListElement [
	super initializeListElement.
	listElement itemType: [ :factory :viewModel :index | self messageElementClassFor: viewModel ]
]

{ #category : 'accessing' }
BVCFairyChatElement >> messageElementClassFor: aViewModel [
	(aViewModel isKindOf: GtLReplyMessageViewModel) ifTrue: [ ^ BVCFairyReplyMessageElement ].
	((aViewModel isKindOf: GtLMessageViewModel) and: [ aViewModel message isUserRole ])
		ifTrue: [ ^ BVCFairyDeveloperMessageElement ].
	^ aViewModel elementClass
]

{ #category : 'updating' }
BVCFairyChatElement >> updateElement [
	"Retain the draft editor and caret on conversation updates. No forced scroll."
	composerElement messageViewModel == chatViewModel newMessageViewModel
		ifFalse: [ composerElement messageViewModel: chatViewModel newMessageViewModel ].
	listElement items: (chatViewModel messageViewModels reject: [ :viewModel | viewModel == chatViewModel newMessageViewModel ])
]
