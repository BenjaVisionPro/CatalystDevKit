Class {
	#name : 'CESimStimulusResolver',
	#superclass : 'CESimResolver',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'resolving' }
CESimStimulusResolver >> patchForStimulusType: aStimulusType transform: aTransform intensity: aNumber target: aNotable inContext: aCESimRunContext [
	"Pure + deterministic. v0: always same patch."

	^ Dictionary new
		at: #lastStimulusType put: aStimulusType;
		at: #lastStimulusIntensity put: aNumber;
		at: #lastStimulusTransform put: aTransform;
		yourself
]
