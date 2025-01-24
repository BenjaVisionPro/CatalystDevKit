Class {
	#name : #BVCHomeMultiCardGetStartedSection,
	#superclass : #GtHomeMultiCardSection,
	#category : #'BV-Catalyst-DevKit-Core-Sections'
}

{ #category : #example }
BVCHomeMultiCardGetStartedSection >> bvcDevKitBookCard [
	<gtSectionCard>
	<gtExample>
	<notest>
	^ GtHomeCard lepiterBase
		title: self bvcDevKitBookName;
		description: 'RTFM';
		priority: 10;
		pageName: self bvcDevKitBookName;
		databaseName: self bvcDevKitBookName;
		readMoreToolbar;
		details: [ :db | 
			| snippets |
			snippets := db pages flatCollect: #allChildrenDepthFirst.
			'The documentation is expressed as a knowledge base. It documents the devKit in '
				, db pages size asString , ' lovely pages containing '
				, snippets size asString , ' snippets of '
				, (snippets groupedBy: #class) size asString , ' different kinds.' ]
				yourself
]

{ #category : #accessing }
BVCHomeMultiCardGetStartedSection >> bvcDevKitBookName [
	^ 'BenjaVision Catalyst DevKit'
]

{ #category : #initialization }
BVCHomeMultiCardGetStartedSection >> defaultPriority [
	^ 30
]

{ #category : #'as yet unclassified' }
BVCHomeMultiCardGetStartedSection >> gemStoneSessionsCard [
	<gtSectionCard>
	<gtExample>
	
	^ GtHomeCard explicit
		priority: 50;
		stencil: [BrFrame new
			background: Color white;
			aptitude: BrShadowAptitude new beLarge;
			geometry: (BlRoundedRectangleGeometry cornerRadius: 2);
			padding: (BlInsets top: 0 bottom: 10 left: 10 right: 10);
			margin: (BlInsets
				top: self spaceGap
				left: 2 * self spaceGap
				bottom: 2 * self spaceGap
				right: 2 * self spaceGap);
			size: 325 @ 150;
			addChild: (GtGemStoneSessionsCardWidget new
				matchParent;
				constraintsDo: [ :c | 
					c frame horizontal alignLeft.
					c frame vertical alignCenter ])]
]

{ #category : #accessing }
BVCHomeMultiCardGetStartedSection >> sectionTitle [
	^ 'Getting Started'
]

{ #category : #'as yet unclassified' }
BVCHomeMultiCardGetStartedSection >> unrealProjectCard [
	<gtSectionCard>
	<gtExample>
	
	^ GtHomeCard explicit
		priority: 50;
		stencil: [BrFrame new
			background: Color white;
			aptitude: BrShadowAptitude new beLarge;
			geometry: (BlRoundedRectangleGeometry cornerRadius: 6);
			padding: (BlInsets top: 0 bottom: 10 left: 10 right: 10);
			margin: (BlInsets
				top: self spaceGap
				left: 2 * self spaceGap
				bottom: 2 * self spaceGap
				right: 2 * self spaceGap);
			size: 750 @ 150;
			addChild: (BVCUnrealProjectCardWidget new
				matchParent;
				constraintsDo: [ :c | 
					c frame horizontal alignLeft.
					c frame vertical alignCenter ])]
]
