"
I represent an ACF GamePlay Tag.
Technically I represent a single row in a DataTable with a GamePlayTagTableRow row type.
However, I also contain nested gamePlayTags allowing me to represent a hierarchy of tags.
See the examples for more information.
"
Class {
	#name : #BVCACFGamePlayTag,
	#superclass : #Object,
	#instVars : [
		'rowName',
		'tag',
		'devComment',
		'parent',
		'children'
	],
	#category : #'BV-Catalyst-ACF-Core'
}

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag class >> parent: aParentTag [
	^ self new
		parent: aParentTag;
		yourself
]

{ #category : #examples }
BVCACFGamePlayTag class >> tag: aString [
	^ self new
		tag: aString;
		yourself
]

{ #category : #'as yet unclassified' }
BVCACFGamePlayTag class >> tag: aTagString devComment: aCommentString [
	^ self new
		tag: aTagString;
		devComment: aCommentString;
		yourself
]

{ #category : #examples }
BVCACFGamePlayTag class >> tgcGamePlayTag [
	<gtExample>
	^ (BVCACFGamePlayTag tag: 'TGC')
		addChild: ((BVCACFGamePlayTag tag: 'Core')
				addChild: (BVCACFGamePlayTag tag: 'Physical');
				addChild: ((BVCACFGamePlayTag tag: 'Offensive')
						addChild: (BVCACFGamePlayTag tag: 'Critical'));
				addChild: (BVCACFGamePlayTag tag: 'Defensive');
				addChild: (BVCACFGamePlayTag tag: 'Utility'))
]

{ #category : #accessing }
BVCACFGamePlayTag >> addChild: aBVCACFGamePlayTag [
	aBVCACFGamePlayTag parent: self.
	children add: aBVCACFGamePlayTag
]

{ #category : #exporting }
BVCACFGamePlayTag >> dataTableRows [
	"Add myself and my children as rows"

	^ OrderedCollection new
		add: self;
		addAll: ((children asSortedCollection: [ :a :b | a tag < b tag ])
				collect: [ :child | child dataTableRows ]) flatten;
		yourself
]

{ #category : #accessing }
BVCACFGamePlayTag >> devComment [
	^ devComment
]

{ #category : #accessing }
BVCACFGamePlayTag >> devComment: aString [
	devComment := aString
]

{ #category : #'gt - views' }
BVCACFGamePlayTag >> gtDataTableFor: aView [
	<gtView>
	^ aView columnedList
		title: 'Data Table';
		priority: 10;
		items: [ self dataTableRows ];
		column: 'Row Name'
			text: [ :item  | item rowName ]
			width: 45;
		column: 'Tag'
			text: [ :item | item tag ]
			width: 150;
		column: 'Dev Comment'
			text: [ :item | item devComment ]
			width: 300;
		actionButtonIcon: BVCDevKitVectorIcons plusCircle
			tooltip: 'Add Tag'
			action: [ :aButton :aTab | aButton phlow spawnObject: self ]
]

{ #category : #initalization }
BVCACFGamePlayTag >> initialize [
	super initialize.
	children := Set new
]

{ #category : #accessing }
BVCACFGamePlayTag >> parent: aParentTag [
	parent := aParentTag
]

{ #category : #accessing }
BVCACFGamePlayTag >> rowName [
	^ rowName
]

{ #category : #accessing }
BVCACFGamePlayTag >> rowName: aString [
	rowName := aString
]

{ #category : #accessing }
BVCACFGamePlayTag >> tag [
	^ tag
]

{ #category : #accessing }
BVCACFGamePlayTag >> tag: aString [
	tag := aString
]
