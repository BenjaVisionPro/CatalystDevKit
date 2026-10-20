"
Live DevKit context and the existing Catalyst Lepiter instruction pages. Contains no credentials and does not mirror the runtime.
"
Class {
	#name : 'BVCDevKitContext',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'tools' }
BVCDevKitContext class >> documentTools [
	^ GtLTools withAll: { BVCFairyDirectoryContentsTool new. BVCFairyFileContentsTool new }
]

{ #category : 'tools' }
BVCDevKitContext class >> readOnlyTools [
	^ GtLTools gtSearch, GtLTools leSearch, self documentTools,
		(GtLTools withAll: { BVCFairyObjectInspectionTool new })
]

{ #category : 'documents' }
BVCDevKitContext >> allowsDocumentDirectory: aReference [
	^ aReference isDirectory and: [
		self repositories anySatisfy: [ :repository |
			self isDocumentReference: aReference under: repository repositoryDirectory ] ]
]

{ #category : 'documents' }
BVCDevKitContext >> allowsDocumentFile: aReference [
	^ self repositories anySatisfy: [ :repository |
		self allowsDocumentFile: aReference under: repository repositoryDirectory ]
]

{ #category : 'documents' }
BVCDevKitContext >> allowsDocumentFile: aReference under: aRepositoryRoot [
	^ (#('md' 'markdown') includes: aReference extension asLowercase)
		and: [ (self isDocumentReference: aReference under: aRepositoryRoot) and: [
			aReference isFile and: [ aReference size <= 262144 ] ] ]
]

{ #category : 'instructions' }
BVCDevKitContext >> configureChat: aChat forRole: aRoleName [
	| rolePageId |
	rolePageId := { 'Barry' -> '95fl487m04zijuwrb2x7h9f5f'.
		'System Explorer' -> '60rxs4qo0lf0hsyj52dihv4da'.
		'System Maintainer' -> '5j28k5ilimindkvqoe9iksabc' } asDictionary
			at: aRoleName ifAbsent: [ self error: 'Unknown Catalyst role: ', aRoleName ].
	aChat instruction: self instructionString titled: 'Current DevKit'.
	aChat pageIdExplanation: self instructionPageIds first from: self knowledgeBase.
	aChat pageIdExplanation: rolePageId from: self knowledgeBase.
	aChat pageIdExplanation: self frameworkOwnershipPageId from: self knowledgeBase.
	aRoleName = 'System Maintainer' ifTrue: [
		aChat
			gtPageExplanation: 'Rules for Moldable Development for Glamorous Toolkit';
			gtPageExplanation: 'Examples by example' ]
]

{ #category : 'accessing' }
BVCDevKitContext >> details [
	^ { 'Image' -> Smalltalk imageFile basename.
		'Platform' -> Smalltalk version.
		'Scope' -> 'Local BVC-built DevKit. Source edits stay in the image.'.
		'Knowledge base' -> self knowledgeBase uuid asString.
		'Projects' -> ((self repositories collect: [ :repository | repository name ]) joinUsing: ', ') }
]

{ #category : 'documents' }
BVCDevKitContext >> documentPathFor: aReference [
	| repository relativePath |
	repository := self repositories
		detect: [ :each | self isDocumentReference: aReference under: each repositoryDirectory ]
		ifNone: [ self error: 'Document is outside the registered DevKit projects.' ].
	relativePath := (aReference relativeTo: repository repositoryDirectory) pathString.
	^ relativePath isEmpty
		ifTrue: [ repository name ]
		ifFalse: [ repository name, '/', relativePath ]
]

{ #category : 'documents' }
BVCDevKitContext >> documentReferenceFor: aProjectPath [
	| segments repository reference |
	aProjectPath isString ifFalse: [ ^ nil ].
	aProjectPath asFileReference isAbsolute ifTrue: [ ^ nil ].
	segments := aProjectPath findTokens: '/'.
	(segments isEmpty or: [ segments anySatisfy: [ :segment | segment beginsWith: '.' ] ])
		ifTrue: [ ^ nil ].
	repository := self repositories
		detect: [ :each | each name = segments first ]
		ifNone: [ ^ nil ].
	reference := segments allButFirst
		inject: repository repositoryDirectory
		into: [ :directory :segment | directory / segment ].
	^ (self isDocumentReference: reference under: repository repositoryDirectory)
		ifTrue: [ reference ]
		ifFalse: [ nil ]
]

{ #category : 'accessing' }
BVCDevKitContext >> frameworkOwnershipPageId [
	^ '5qshvxjwkjikwkx6tbpazkgqs'
]

{ #category : 'accessing' }
BVCDevKitContext >> instructionPageIds [
	^ #('auvrpe1mgrddsq94kz9x9s17h' '95fl487m04zijuwrb2x7h9f5f'
		'60rxs4qo0lf0hsyj52dihv4da' '5j28k5ilimindkvqoe9iksabc'),
		{ self frameworkOwnershipPageId }
]

{ #category : 'accessing' }
BVCDevKitContext >> instructionPages [
	^ self instructionPageIds collect: [ :pageId |
		self knowledgeBase pageWithID: pageId
			ifAbsent: [ self error: 'A Catalyst instruction page is missing: ', pageId ] ]
]

{ #category : 'instructions' }
BVCDevKitContext >> instructionString [
	^ String streamContents: [ :stream |
		stream nextPutAll: 'Context discovered from the running DevKit. Inspect loaded classes and methods for current behavior.'; cr.
		stream nextPutAll: 'Source edits stay in the image. Saving source files, committing and pushing are separate user-authorized actions through the existing GT Git or Iceberg tools for this DevKit. Do not discover, copy or synchronize external checkouts.'; cr.
		stream nextPutAll: 'Read documentation through registered Lepiter books or project-relative document references such as CatalystRuntime/runtime. Document paths are read-only evidence, not source-edit or export targets.'; cr.
		self details do: [ :detail |
			stream nextPutAll: detail key; nextPutAll: ': '; nextPutAll: detail value; cr ] ]
]

{ #category : 'documents' }
BVCDevKitContext >> isDocumentReference: aReference under: aRepositoryRoot [
	"Compare path components, exclude hidden paths and reject symlink ancestors."
	aReference isAbsolute ifFalse: [ ^ false ].
	(aReference path segments anySatisfy: [ :segment | segment beginsWith: '.' ])
		ifTrue: [ ^ false ].
	(aReference = aRepositoryRoot or: [ aRepositoryRoot containsReference: aReference ])
		ifFalse: [ ^ false ].
	^ aReference withParents noneSatisfy: [ :ancestor |
		ancestor isRoot not and: [ ancestor isSymlink ] ]
]

{ #category : 'accessing' }
BVCDevKitContext >> knowledgeBase [
	^ LeDatabasesRegistry defaultLogicalDatabase
		databaseWithID: '731asfxqhyhdr96k6wo9yxnzv'
		ifNone: [ self error: 'The Catalyst DevKit knowledge base is not registered.' ]
]

{ #category : 'accessing' }
BVCDevKitContext >> repositories [
	^ (IceRepository registry select: [ :repository |
		repository name beginsWith: 'Catalyst' ])
			asSortedCollection: [ :left :right | left name < right name ]
]
