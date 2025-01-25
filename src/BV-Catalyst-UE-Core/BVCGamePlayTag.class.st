"
I represent an ACF GamePlay Tag.
Technically I represent a single row in a DataTable with a GamePlayTagTableRow row type.
However, I also contain nested gamePlayTags allowing me to represent a hierarchy of tags.
See the examples for more information.
"
Class {
	#name : #BVCGamePlayTag,
	#superclass : #Object,
	#instVars : [
		'rowName',
		'tag',
		'devComment',
		'parent',
		'children'
	],
	#category : #'BV-Catalyst-UE-Core'
}

{ #category : #'instance creation' }
BVCGamePlayTag class >> parent: aParentTag [
	^ self new
		parent: aParentTag;
		yourself
]

{ #category : #'instance creation' }
BVCGamePlayTag class >> tag: aString [
	^ self new
		tag: aString;
		yourself
]

{ #category : #'instance creation' }
BVCGamePlayTag class >> tag: aTagString devComment: aCommentString [
	^ self new
		tag: aTagString;
		devComment: aCommentString;
		yourself
]

{ #category : #accessing }
BVCGamePlayTag >> addChild: aBVCACFGamePlayTag [
	aBVCACFGamePlayTag parent: self.
	children add: aBVCACFGamePlayTag
]

{ #category : #accessing }
BVCGamePlayTag >> children [
	^ children
]

{ #category : #exporting }
BVCGamePlayTag >> dataTableRows [
	"Add myself and my children as rows"

	^ OrderedCollection new
		add: self;
		addAll: ((children asSortedCollection: [ :a :b | a tag < b tag ])
				collect: [ :child | child dataTableRows ]) flatten;
		yourself
]

{ #category : #accessing }
BVCGamePlayTag >> devComment [
	^ devComment
]

{ #category : #accessing }
BVCGamePlayTag >> devComment: aString [
	devComment := aString
]

{ #category : #exporting }
BVCGamePlayTag >> export [
	self
		exportCSVOnPath: (String
				streamContents: [ :stream | 
					stream
						nextPutAll: '/Users/jupiter/Documents/Unreal Projects/ThatGameCatalyst/Content/GamePlayTags/';
						nextPutAll: tag;
						nextPutAll: '.csv' ])
]

{ #category : #exporting }
BVCGamePlayTag >> exportCSVOnPath: aPath [
	| fileStream csvWriter |
	fileStream := File openForWriteFileNamed: aPath.
	csvWriter := NeoCSVWriter on: fileStream.
	csvWriter
		addFields: #(#exportRowName #exportTag #exportDevComment);
		writeHeader: #('RowName' 'Tag' 'DevComment');
		nextPutAll: self dataTableRows.
	fileStream close
]

{ #category : #accessing }
BVCGamePlayTag >> exportDevComment [
	^ devComment
		ifNil: [ children ifEmpty: [ ^ '' ].
			children
				ifNotEmpty: [ String
						streamContents: [ :stream | 
							self tagPathToRoot
								do: [ :item | 
									stream
										nextPutAll: item tag;
										nextPut: $  ].
							stream nextPutAll: 'Tag Root' ] ] ]
]

{ #category : #accessing }
BVCGamePlayTag >> exportRowName [
	^ rowName ifNil: [ self tagPathString ]
]

{ #category : #accessing }
BVCGamePlayTag >> exportTag [
	^ rowName ifNil: [ self tagPathString ]
]

{ #category : #'gt - views' }
BVCGamePlayTag >> graph [
	<gtExample>
	| m |
	m := GtMondrian new.
	m nodes
		stencil: [ :nodeTag | 
			BlElement new
				border: (BlBorder paint: Color black width: 0.8);
				geometry: BlRoundedRectangleGeometry new;
				size: 10 @ 3;
				when: BlMouseEnterEvent
					do: [ :anEvent | 
						anEvent currentTarget graph connectedEdges
							do: [ :inner | inner element border: (BlBorder paint: (Color red alpha: 0.5)) ] ];
				when: BlMouseLeaveEvent
					do: [ :anEvent | 
						anEvent currentTarget graph connectedEdges
							do: [ :inner | inner element border: (BlBorder paint: (Color blue alpha: 0.5)) ] ] ];
		with: self dataTableRows.
	m edges
		stencil: [ :nodeTag | 
			BlLineElement new
				zIndex: -1;
				border: (BlBorder paint: (Color blue alpha: 0.5)) ];
		connectFrom: [ :nodeTag | nodeTag parent ].
	m layout force.
	^ m
]

{ #category : #'gt - views' }
BVCGamePlayTag >> gtDataTableFor: aView [
	<gtView>
	^ aView columnedList
		title: 'Data Table';
		priority: 10;
		items: [ self dataTableRows ];
		column: 'Row Name'
			text: [ :item  | item exportRowName ]
			width: 350;
		column: 'Tag'
			text: [ :item | item tagPathString ]
			width: 350;
		column: 'Dev Comment'
			text: [ :item | item exportDevComment ]
			width: 300;
		actionButtonIcon: BVCDevKitVectorIcons plusCircle
			tooltip: 'Add Tag'
			action: [ :aButton :aTab | aButton phlow spawnObject: self ]
]

{ #category : #'gt - views' }
BVCGamePlayTag >> gtVisualisationFor: aView [
	<gtView>
	^ aView explicit
		title: 'Graph';
		priority: 5;
		stencil: [ self graph ]
]

{ #category : #initalization }
BVCGamePlayTag >> initialize [
	super initialize.
	children := Set new
]

{ #category : #accessing }
BVCGamePlayTag >> parent [
	^ parent
]

{ #category : #accessing }
BVCGamePlayTag >> parent: anObject [
	parent := anObject
]

{ #category : #accessing }
BVCGamePlayTag >> rowName [
	^ rowName
]

{ #category : #accessing }
BVCGamePlayTag >> rowName: aString [
	rowName := aString
]

{ #category : #accessing }
BVCGamePlayTag >> tag [
	^ tag
]

{ #category : #accessing }
BVCGamePlayTag >> tag: aString [
	tag := aString
]

{ #category : #accessing }
BVCGamePlayTag >> tagPathString [
	^ String
		streamContents: [ :stream | 
			self tagPathToRoot reversed
				do: [ :item | stream nextPutAll: item tag ]
				separatedBy: [ stream nextPut: $. ] ]
]

{ #category : #accessing }
BVCGamePlayTag >> tagPathToRoot [
	| path |
	path := OrderedCollection with: self.
	parent ifNotNil: [ path addAll: parent tagPathToRoot ].
	^ path
]
