Class {
	#name : 'CRRuntimeOverviewWidget',
	#superclass : 'BrVerticalPane',
	#instVars : [
		'runtime',
		'header',
		'displayNameEditor',
		'elementUpdater',
		'powerButton',
		'powerIcon'
	],
	#category : 'BV-Catalyst-Runtime-UI',
	#package : 'BV-Catalyst-Runtime-UI'
}

{ #category : 'private - children' }
CRRuntimeOverviewWidget >> buildContent [
	"I build my header/dashboard surface."

	self
		hMatchParent;
		vFitContent;
		addChild: (header := self createHeader) as: #header
]

{ #category : 'private - ui' }
CRRuntimeOverviewWidget >> createDisplayNameEditor [
	"I build an editable label for the runtime display name."

	| editor |
	editor := BrEditableLabel new
			hMatchParent;
			vFitContent;
			aptitude: (BrGlamorousEditableLabelAptitude new
					glamorousRegularFont;
					fontSize: 18;
					yourself);
			margin: (BlInsets
					top: 0
					right: 5
					bottom: 3
					left: 0);
			yourself.
	editor
		when: BlBlurEvent
		do: [ :evt | runtime ifNotNil: [ runtime displayName: editor text asString ] ].

	^ editor
]

{ #category : 'private - ui' }
CRRuntimeOverviewWidget >> createHeader [
	"I build the header row: logo + editable runtime name + power button."

	| row logo spacer |
	row := BrHorizontalPane new
			hMatchParent;
			vFitContent;
			layout: BlLinearLayout horizontal alignCenterLeft;
			"padding: (BlInsets all: 8);
			cellSpacing: 8;"
			yourself.

	logo := (BVCDevKitVectorIcons icon: #bvcServer size: 72 @ 72) asElement.

	displayNameEditor := self createDisplayNameEditor.	
	
	"Spacer pushes the power button to the right."
	spacer := BlElement new
			padding: (BlInsets all: 8);
			yourself.

	self createPowerButton.

	row
		addChild: logo;
		addChild: displayNameEditor;
		addChild: spacer;
		addChild: powerButton.

	^ row
]

{ #category : 'private - ui' }
CRRuntimeOverviewWidget >> createPowerButton [
	"I build the power toggle button and keep the icon element so I can recolor it."

	powerButton := BrButton new
			aptitude: BrGlamorousButtonWithIconCircularAptitude new;
			action: [ :aButton | self toggleRuntimeFrom: aButton ];
			yourself.
	self updatePowerButton.
	^ powerButton
]

{ #category : 'initialization' }
CRRuntimeOverviewWidget >> initialize [
	"I build my UI and set up a safe updater."

	super initialize.
	self buildContent.

	elementUpdater := BrElementUpdater new element: self selector: #updateContent
]

{ #category : 'private - hooks' }
CRRuntimeOverviewWidget >> onAddedToSceneGraph [
	"I refresh visual state once I'm visible."

	super onAddedToSceneGraph.
]

{ #category : 'updating' }
CRRuntimeOverviewWidget >> requestContentUpdate [
	"I request an async refresh of my content."

	elementUpdater ifNil: [ ^ self ].
	elementUpdater requestUpdate
]

{ #category : 'accessing' }
CRRuntimeOverviewWidget >> runtime [
	"I answer the runtime I display."

	^ runtime
]

{ #category : 'accessing' }
CRRuntimeOverviewWidget >> runtime: aRuntime [
	"I set the runtime I display and refresh."

	runtime := aRuntime.
	self requestContentUpdate
]

{ #category : 'private - ui' }
CRRuntimeOverviewWidget >> runtimeStatusSummary [
	"I answer a short human status string for tooltips."

	runtime ifNil: [ ^ 'No runtime bound' ].

	^ runtime isRunning ifTrue: [ 'Running' ] ifFalse: [ 'Stopped' ]
]

{ #category : 'actions - ui' }
CRRuntimeOverviewWidget >> toggleRuntimeFrom: aButton [
	"I toggle the runtime running state and refresh the button state."

	runtime ifNil: [ ^ self ].

	runtime isRunning ifTrue: [ runtime stop ] ifFalse: [ runtime start ].
]

{ #category : 'updating' }
CRRuntimeOverviewWidget >> updateContent [
	"I refresh my UI from the current runtime state."

	runtime ifNil: [ ^ self ].

	displayNameEditor
		ifNotNil: [ displayNameEditor
				text: (runtime displayName ifNil: [ 'Catalyst Runtime' ]) asRopedText ]
]

{ #category : 'private - ui' }
CRRuntimeOverviewWidget >> updatePowerButton [
	"I update the power icon background color + tooltip based on runtime state."

	| statusColor |
	statusColor := runtime isRunning
			ifTrue: [ Color green ]
			ifFalse: [ Color black ].
	powerIcon := (BVCDevKitVectorIcons powerSourceColor: statusColor) asElement
			asScalableElement size: 64 @ 64.
		powerButton icon: powerIcon.
]
