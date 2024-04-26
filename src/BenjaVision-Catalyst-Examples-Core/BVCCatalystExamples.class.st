Class {
	#name : #BVCCatalystExamples,
	#superclass : #Object,
	#category : #'BenjaVision-Catalyst-Examples-Core'
}

{ #category : #accessing }
BVCCatalystExamples >> umlClasses [
	<gtExample>
	| view |
	view := GtMondrian new.
	view nodes
		umlClassShapeWithName: [ :each | each name copyFrom: 4 to: each name size ];
		with: BVCInfrastructureComponent withAllSubclasses;
		forEach: [ :class | 
			view nodes
				shape: [ :method | 
					BlTextElement new
						text: method selector asRopedText;
						padding:
							(BlInsets
								top: 5
								right: 5
								bottom: 5
								left: 5) ];
				with: class methods.
			view layout custom: BlLinearLayout vertical ].
	view edges 
		fromCenterBottom;
		toCenterTop;
		connectFrom: #superclass.
	view layout tree levelDistance: 80.
	^ view
]
