Class {
	#name : #BVCDevKitHome,
	#superclass : #GtHome,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #initialization }
BVCDevKitHome >> backgroundIcon [
	^ (BVCDevKitVectorIcons gray: #bvcServer) value asElement asScalableElement
		constraintsDo: [ :c | 
			c ignoreByLayout.
			c ignored horizontal alignCenterAt: 1.0.
			c ignored vertical alignCenterAt: 1.0 ];
		yourself
]

{ #category : #building }
BVCDevKitHome >> createVersionLabel [
	^ BrButton new 
		label: 'BVC DevKit ', GtImage instance version versionString; 
		beSmallSize;
		aptitude: (BrGlamorousButtonWithLabelAptitude new + (BrGlamorousButtonExteriorAptitude new borderPaint: Color transparent; backgroundPaint: Color transparent));
		margin: (BlInsets all: 5);
		constraintsDo: [ :c | c linear horizontal alignRight ];
		action: [ :button | 
			| database startPage |
			database := LeDatabasesRegistry default currentLoadedDefaultLogicalDatabase 
				databaseNamed: 'BenjaVision Catalyst DevKit'.
			startPage := database pageNamed: 'About BVC DevKit'.
			GtWorldUtility 
				showSpaceWithTitle: startPage title
				inPagerWith: [ startPage
					asLepiterPagePhlowTool asElementDo: [ :e | e ] ] asStencil
				from: button ]
]

{ #category : #building }
BVCDevKitHome >> getStartedSection [
	<gtHomeSection>
	<gtExample>
	<noTest>
	^ BVCHomeMultiCardGetStartedSection new
]

{ #category : #initialization }
BVCDevKitHome >> initialize [
	super initialize.
	self addChildFirst: self backgroundIcon
]
