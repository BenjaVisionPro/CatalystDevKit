Class {
	#name : #BVCHomeMultiCardGetStartedSection,
	#superclass : #GtHomeMultiCardSection,
	#category : #'BV-Catalyst-DevKit-Core-Sections'
}

{ #category : #example }
BVCHomeMultiCardGetStartedSection >> aboutThisBookCard [
	"<gtSectionCard>"
	<gtExample>
	<notest>
	^ GtHomeCard page
		priority: 20;
		pageName: 'About this book';
		databaseName: self gtBookName;
		yourself
]

{ #category : #initialization }
BVCHomeMultiCardGetStartedSection >> defaultPriority [
	^ 30
]

{ #category : #example }
BVCHomeMultiCardGetStartedSection >> gtBookCard [
	<gtSectionCard>
	<gtExample>
	<notest>
	^ GtHomeCard lepiterBase
		title: 'BenjaVision Catalyst DevKit';
		description: 'RTFM';
		priority: 10;
		pageName: 'Glamorous Toolkit';
		databaseName: self gtBookName;
		details: [ :db | 
			| snippets |
			snippets := db pages flatCollect: #allChildrenDepthFirst.
			'The book is expressed as a knowledge base. It documents the environment in '
				, db pages size asString , ' lovely pages containing '
				, snippets size asString , ' snippets of '
				, (snippets groupedBy: #class) size asString , ' different kinds.' ]
				yourself
]

{ #category : #example }
BVCHomeMultiCardGetStartedSection >> gtBookCardSection [
	<gtExample>
	<notest>
	^ self
]

{ #category : #accessing }
BVCHomeMultiCardGetStartedSection >> gtBookName [
	^ 'Glamorous Toolkit Book'
]

{ #category : #example }
BVCHomeMultiCardGetStartedSection >> gtTourCard [
	<gtExample>
	^ GtHomeCard job
		title: 'GtTour';
		description: 'Open the GtTour slideshow';
		priority: 20;
		block: [ GtPresenterSlideShow openInSpace: GtTour ];
		yourself
]

{ #category : #accessing }
BVCHomeMultiCardGetStartedSection >> sectionTitle [
	^ 'Getting Started'
]
