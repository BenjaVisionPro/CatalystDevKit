Extension { #name : 'BVCHomeMultiCardGetStartedSection' }

{ #category : '*bv-catalyst-runtime-ui' }
BVCHomeMultiCardGetStartedSection >> catalystRuntimesCard [
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
			addChild: (CRRuntimeCardWidget new
				matchParent;
				constraintsDo: [ :c | 
					c frame horizontal alignLeft.
					c frame vertical alignCenter ])]
]
