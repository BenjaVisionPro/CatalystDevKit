Extension { #name : 'GtLChatRegistry' }

{ #category : '*BV-Catalyst-Fairy-Core' }
GtLChatRegistry >> newCatalystChatDescription [
	<gtLlmRegistry>
	^ GtLChatRegistryDescription new
		label: 'Catalyst Chat';
		priority: 40;
		chat: [ :provider | self newCatalystChatWithProvider: provider ]
]

{ #category : '*BV-Catalyst-Fairy-Core' }
GtLChatRegistry >> newCatalystChatWithProvider: aProvider [
	| chat |
	chat := BVCFairyChat new.
	aProvider ifNotNil: [ chat provider: aProvider ].
	^ self registerChat: chat
]
