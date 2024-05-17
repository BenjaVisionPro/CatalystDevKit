Class {
	#name : #BaselineOfCatalystDevKit,
	#superclass : #BaselineOf,
	#category : #BaselineOfCatalystDevKit
}

{ #category : #baseline }
BaselineOfCatalystDevKit >> baseline: spec [
	<baseline>
	^ spec
		for: #common
		do: [ spec
				package: 'BenjaVision-Catalyst-Core';
				package: 'BenjaVision-Catalyst-Connect-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Core') ];
				package: 'BenjaVision-Catalyst-Store-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Connect-Core') ];
				package: 'BenjaVision-Catalyst-Users-Messages-Core';
				package: 'BenjaVision-Catalyst-Users-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Store-Core') ];
				package: 'BenjaVision-Catalyst-Groups-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Store-Core') ];
				package: 'BenjaVision-Catalyst-Currency-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Store-Core') ];
				package: 'BenjaVision-Catalyst-Landform-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Store-Core') ];
				package: 'BenjaVision-Catalyst-Architect-Core'
					with: [ spec requires: #('BenjaVision-Catalyst-Store-Core') ];
				package: 'BenjaVision-Catalyst-Examples-Core';
				package: 'BenjaVision-Catalyst-Setup-Core' ]
]
