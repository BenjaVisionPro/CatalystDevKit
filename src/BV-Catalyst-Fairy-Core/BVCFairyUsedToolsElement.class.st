"
Selects Barry tool activity rows on the inherited execution-message stream. Generic GT lists are unchanged.
"
Class {
	#name : 'BVCFairyUsedToolsElement',
	#superclass : 'GtLMessageUsedToolsElement',
	#category : 'BV-Catalyst-Fairy-Core-UI',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'UI'
}

{ #category : 'initialization' }
BVCFairyUsedToolsElement >> newListItemElement [
	^ BVCFairyToolActivityElement new
		addAptitude: BrGlamorousListItemAptitude;
		hMatchParent;
		vFitContent
]
