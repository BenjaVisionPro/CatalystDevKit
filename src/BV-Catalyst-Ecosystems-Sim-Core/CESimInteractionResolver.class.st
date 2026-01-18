Class {
	#name : 'CESimInteractionResolver',
	#superclass : 'CESimResolver',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'resolving' }
CESimInteractionResolver >> patchForInteractionType: anInteractionType payload: aPayload target: aNotable inContext: aCESimRunContext [
	"Pure + deterministic. Return only the keys this interaction affects."

	^ Dictionary new
		at: #lastInteractionType put: anInteractionType;
		at: #lastInteractionPayload put: aPayload;
		yourself
]
