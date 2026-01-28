Class {
	#name : 'CRRuntimeCardWidget',
	#superclass : 'BrVerticalPane',
	#instVars : [
		'registry',
		'runtimeList',
		'elementUpdater'
	],
	#category : 'BV-Catalyst-Runtime-UI',
	#package : 'BV-Catalyst-Runtime-UI'
}

{ #category : 'callbacks' }
CRRuntimeCardWidget >> actOnRegistryAnnouncement [
	"I refresh when the registry changes."

	self requestContentUpdate
]

{ #category : 'private-children' }
CRRuntimeCardWidget >> buildContent [
	"I build my list and toolbar."

	self
		addChild: (runtimeList := self createListWithItems) as: #runtimeList;
		addChild: self createToolbar
]

{ #category : 'actions-ui' }
CRRuntimeCardWidget >> createAndSelectNewRuntime [
	"I create a new runtime, start it, and select it."

	| rt |
	rt := CRRuntime new start.
	self requestContentUpdate.
	self selectRuntime: rt
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> createInspectRegistryButton [
	"I open an inspector on the runtime registry."

	^ BrButton new
		aptitude: BrGlamorousButtonWithIconAptitude new;
		icon: BrGlamorousVectorIcons inspect;
		label: 'Inspect';
		action: [ :aButton | self inspectRegistryFrom: aButton ];
		yourself
]

{ #category : 'private-children' }
CRRuntimeCardWidget >> createList [
	"I create the runtimes list."

	| list |
	list := BrColumnedList new.

	list column
		title: 'Name';
		width: 165;
		cellStencil: [ BrLabel new aptitude: BrGlamorousLabelAptitude new ];
		dataBinder: [ :aLabel :aRuntime | aLabel text: (aRuntime displayName ifNil: [ aRuntime printString ]) ].

	list column
		title: 'Run';
		width: 45;
		cellStencil: [ BrLabel new aptitude: BrGlamorousLabelAptitude new ];
		dataBinder: [ :aLabel :aRuntime | aLabel text: (aRuntime isRunning ifTrue: [ '✓' ] ifFalse: [ '-' ]) ].

	list column
		title: 'W';
		width: 30;
		cellStencil: [ BrLabel new aptitude: BrGlamorousLabelAptitude new ];
		dataBinder: [ :aLabel :aRuntime | aLabel text: aRuntime workers size asString ].

	list when: BrSelectionDoubleClicked do: [ :evt | self doDoubleClicked: evt ].

	list
		rowStencil: self createRowStencil;
		padding: (BlInsets top: 5);
		matchParent.

	^ list
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> createListWithItems [
	"I create the list populated with current items."

	| list |
	list := self createList.
	list items: self runtimesToDisplay.
	^ list
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> createNewRuntimeButton [
	"I create a new runtime and start it."

	^ BrButton new
		aptitude: BrGlamorousButtonWithIconAptitude new;
		icon: BrGlamorousVectorIcons add;
		label: 'New runtime';
		action: [ :aButton | self createAndSelectNewRuntime ];
		yourself
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> createRefreshButton [
	"I refresh the displayed list."

	^ BrButton new
		aptitude: BrGlamorousButtonWithIconAptitude new;
		icon: BrGlamorousVectorIcons refresh;
		label: 'Refresh';
		action: [ :aButton | self requestContentUpdate ];
		yourself
]

{ #category : 'private-children' }
CRRuntimeCardWidget >> createRowStencil [
	"I add a context menu per row."

	^ BrColumnedListItemElementWithContextMenuDecorator new
		stencilBuilder: BrGlamorousColumnedListSelectableRowElementStencilBuilder new;
		contextMenuStencil: [ :anElement :aRuntime | self runtimeActionsFor: aRuntime ]
]

{ #category : 'private-children' }
CRRuntimeCardWidget >> createTitleLabel [
	"I show the card title."

	^ BrLabel new
		aptitude: BrGlamorousLabelAptitude new;
		hMatchParent;
		vFitContent;
		text: 'Catalyst Runtime' asRopedText bold
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> createToolbar [
	"I lay out my toolbar."

	^ BrHorizontalPane new
		hMatchParent;
		vFitContent;
		layout: BlLinearLayout horizontal alignTopRight;
		addChild: self createTitleLabel;
		addChild: (self createNewRuntimeButton margin: (BlInsets right: 5));
		addChild: (self createRefreshButton margin: (BlInsets right: 5));
		addChild: self createInspectRegistryButton;
		yourself
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> doDoubleClicked: anEvent [
	"I inspect a runtime on double click."

	| runtime |
	runtime := anEvent currentTarget items at: anEvent selection first.
	runtime class = CRRuntimeCardWidgetNoRuntimes ifTrue: [ ^ self ].
	self inspectRuntime: runtime from: anEvent currentTarget
]

{ #category : 'initialization' }
CRRuntimeCardWidget >> initialize [
	"I build my UI and set up a safe updater."

	super initialize.
	self buildContent.

	elementUpdater := BrElementUpdater new element: self selector: #updateContent
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> inspectRegistryFrom: aButton [
	"I open a pager inspector on the registry."

	GtPager
		openWrappedOn: (GtInspector newOn: self registry)
		title: 'Catalyst Runtime Registry'
		from: aButton
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> inspectRuntime: aRuntime from: anElement [
	"I open a pager inspector on a runtime."

	GtPager
		openWrappedOn: (GtInspector newOn: aRuntime)
		title: (aRuntime displayName ifNil: [ 'Runtime' ])
		from: anElement
]

{ #category : 'private-hooks' }
CRRuntimeCardWidget >> onAddedToSceneGraph [
	"I refresh once I'm visible."

	super onAddedToSceneGraph.
	self requestContentUpdate
]

{ #category : 'accessing' }
CRRuntimeCardWidget >> registry [
	"I answer the runtime registry I display."

	^ registry
		ifNil: [ registry := CRRuntimeRegistry default.
			registry ]
]

{ #category : 'updating' }
CRRuntimeCardWidget >> requestContentUpdate [
	"I request an async refresh of my content."

	elementUpdater ifNil: [ ^ self ].
	elementUpdater requestUpdate
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> runtimeActionsFor: aRuntime [
	"I offer actions for a runtime."

	| actions |
	aRuntime class = CRRuntimeCardWidgetNoRuntimes
		ifTrue: [ ^ BrGlamorousSimpleContextMenuContent new ].

	actions := OrderedCollection new.

	aRuntime isRunning
		ifTrue: [ actions
				add: 'Stop'
						-> [ :el | 
							aRuntime stop.
							self requestContentUpdate ] ]
		ifFalse: [ actions
				add: 'Start'
						-> [ :el | 
							aRuntime start.
							self requestContentUpdate ] ].

	actions addAll: {'Inspect' -> [ :el | self inspectRuntime: aRuntime from: el ]}.

	^ BrGlamorousSimpleContextMenuContent new items: actions
]

{ #category : 'accessing' }
CRRuntimeCardWidget >> runtimeList [
	"I answer my list widget."

	^ self childNamed: #runtimeList
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> runtimesToDisplay [
	"I answer the runtimes to show, or a placeholder row if empty."

	^ (self registry runtimes asArray
		sorted: [ :a :b | (a displayName ifNil: [ '' ]) <= (b displayName ifNil: [ '' ]) ])
		ifEmpty: [ {CRRuntimeCardWidgetNoRuntimes new} ]
]

{ #category : 'actions-ui' }
CRRuntimeCardWidget >> selectRuntime: aRuntime [
	"I select a runtime in my list."

	| index |
	index := self runtimeList items indexOf: aRuntime.
	index > 0 ifTrue: [ self runtimeList selectOne: index ]
]

{ #category : 'private-ui' }
CRRuntimeCardWidget >> updateContent [
	"I refresh my list while preserving selection when possible."

	| selected |
	selected := self runtimeList selectedItems
			ifEmpty: [ nil ]
			ifNotEmpty: [ :sel | sel first ].

	self
		replaceChild: self runtimeList
		with: self createListWithItems
		as: #runtimeList.

	selected ifNotNil: [ self selectRuntime: selected ]
]
