"
Focused examples for Barry-local chat presentation without provider requests.
"
Class {
	#name : 'BVCFairyChatElementExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyChatElementExamples >> barryEntryPoint [
	<gtExample>
	| chat element |
	chat := self styledConversation chatViewModel chat.
	element := chat asElement.
	self assert: element children last class equals: BVCFairyChatElement.
	self assert: element children last chatViewModel chat == chat.
	self assert: (GtLChat new asElement class) equals: GtLChatElement.
	^ element
]

{ #category : 'examples' }
BVCFairyChatElementExamples >> fixedComposerAndDraft [
	<gtExample>
	| element composer draft |
	element := self styledConversation.
	composer := element children last.
	draft := element chatViewModel newMessageViewModel.
	draft contents: 'Unsent multiline draft' , String lf , 'second line' source: self.
	element updateElement.
	self assert: element children last == composer.
	self assert: composer messageViewModel == draft.
	self assert: draft contents asString equals: 'Unsent multiline draft' , String lf , 'second line'.
	element size: 800 @ 600.
	element forceLayout.
	self assert: element children first bounds inParent bottom <= composer bounds inParent top.
	self assert: composer bounds inParent bottom <= 600.
	self assert: composer bounds inParent height > 0.
	^ element
]

{ #category : 'examples' }
BVCFairyChatElementExamples >> messagePresentations [
	<gtExample>
	| conversation models developer reply pane |
	conversation := self styledConversation.
	models := conversation chatViewModel messageViewModels.
	developer := BVCFairyDeveloperMessageElement newForChatList messageViewModel: models first; yourself.
	reply := BVCFairyReplyMessageElement newForChatList messageViewModel: models second; yourself.
	self assert: developer margin left > developer margin right.
	self assert: reply background isTransparent.
	self assert: reply children first children first id equals: #catalystResponseFairy asBlocElementId.
	pane := BrVerticalPane new hExact: 800; vFitContent; addChild: developer; addChild: reply; yourself.
	pane forceLayout.
	^ pane
]

{ #category : 'examples' }
BVCFairyChatElementExamples >> styledConversation [
	<gtExample>
	| chat provider messages viewModel element developer reply assistant developerElement replyElement |
	chat := BVCFairyExamples new parentChat.
	provider := chat provider.
	messages := chat messages.
	developer := GtLModelUserMessage new markdown: 'Please explain this code.'; yourself.
	chat addMessage: developer.
	assistant := GtLOpenAIAssistantMessage new
		chat: chat;
		rawData: (Dictionary new at: 'content' put: { Dictionary new at: 'text' put: 'Barry response with existing GT document rendering.'; yourself }; yourself);
		yourself.
	reply := GtLReplyMessage new userMessage: developer; finalMessage: assistant; yourself.
	chat addMessage: reply.
	viewModel := chat asViewModel.
	element := BVCFairyChatElement new chatViewModel: viewModel.
	self assert: chat provider == provider.
	self assert: chat messages == messages.
	self assert: element children size equals: 2.
	self assert: element children last class equals: GtLNewMessageElement.
	self assert: element children last messageViewModel == viewModel newMessageViewModel.
	self assert: element children first items size equals: 2.
	developerElement := (element messageElementClassFor: viewModel messageViewModels first) newForChatList
		messageViewModel: viewModel messageViewModels first; yourself.
	replyElement := (element messageElementClassFor: viewModel messageViewModels second) newForChatList
		messageViewModel: viewModel messageViewModels second; yourself.
	self assert: developerElement class equals: BVCFairyDeveloperMessageElement.
	self assert: replyElement class equals: BVCFairyReplyMessageElement.
	self assert: replyElement messageViewModel message == reply.
	^ element
]
