"Live DevKit context and the existing Catalyst Lepiter instruction pages. Contains no credentials and does not mirror the runtime."
Class {
	#name : #BVCDevKitContext,
	#superclass : #Object,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCDevKitContext >> knowledgeBase [
	^ LeDatabasesRegistry defaultLogicalDatabase
		databaseWithID: '731asfxqhyhdr96k6wo9yxnzv'
		ifNone: [ self error: 'The Catalyst DevKit knowledge base is not registered.' ]
]

{ #category : #accessing }
BVCDevKitContext >> instructionPageIds [
	^ #('auvrpe1mgrddsq94kz9x9s17h' '95fl487m04zijuwrb2x7h9f5f'
		'60rxs4qo0lf0hsyj52dihv4da' '5j28k5ilimindkvqoe9iksabc')
]

{ #category : #accessing }
BVCDevKitContext >> instructionPages [
	^ self instructionPageIds collect: [ :pageId |
		self knowledgeBase pageWithID: pageId
			ifAbsent: [ self error: 'A Catalyst instruction page is missing: ', pageId ] ]
]

{ #category : #accessing }
BVCDevKitContext >> repositories [
	^ (IceRepository registry select: [ :repository |
		repository name beginsWith: 'Catalyst' ])
			asSortedCollection: [ :left :right | left name < right name ]
]

{ #category : #accessing }
BVCDevKitContext >> details [
	^ { 'Image' -> Smalltalk imageDirectory fullName.
		'Platform' -> Smalltalk version.
		'Scope' -> 'Local BVC-built DevKit. Production mutation and remote GemStone tools are unavailable.'.
		'Knowledge base' -> self knowledgeBase uuid asString },
		(self repositories collect: [ :repository |
			repository name -> repository repositoryDirectory fullName ]) asArray
]

{ #category : #instructions }
BVCDevKitContext >> instructionString [
	^ String streamContents: [ :stream |
		stream nextPutAll: 'Context discovered from this running DevKit. Repository paths identify loaded checkouts; inspect source for current behavior.'; cr.
		self details do: [ :detail |
			stream nextPutAll: detail key; nextPutAll: ': '; nextPutAll: detail value; cr ] ]
]

{ #category : #instructions }
BVCDevKitContext >> configureChat: aChat forRole: aRoleName [
	| rolePageId |
	rolePageId := { 'Barry' -> '95fl487m04zijuwrb2x7h9f5f'.
		'System Explorer' -> '60rxs4qo0lf0hsyj52dihv4da'.
		'System Maintainer' -> '5j28k5ilimindkvqoe9iksabc' } asDictionary
			at: aRoleName ifAbsent: [ self error: 'Unknown Catalyst role: ', aRoleName ].
	aChat instruction: self instructionString titled: 'Current DevKit'.
	aChat pageIdExplanation: self instructionPageIds first from: self knowledgeBase.
	aChat pageIdExplanation: rolePageId from: self knowledgeBase.
	aRoleName = 'System Maintainer' ifTrue: [
		aChat
			gtPageExplanation: 'Rules for Moldable Development for Glamorous Toolkit';
			gtPageExplanation: 'Examples by example' ]
]
