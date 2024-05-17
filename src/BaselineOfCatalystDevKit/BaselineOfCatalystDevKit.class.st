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
				package: 'BV-Catalyst-Core';
				package: 'BV-Catalyst-Connect-Core'
					with: [ spec requires: #('BV-Catalyst-Core') ];
				package: 'BV-Catalyst-Store-Core'
					with: [ spec requires: #('BV-Catalyst-Connect-Core') ];
				package: 'BV-Catalyst-Users-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-Users-Messages-Core'
					with: [ spec requires: #('BV-Catalyst-Users-Core') ];
				package: 'BV-Catalyst-Groups-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-Currency-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-Landform-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-Architect-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-Examples-Core';
				package: 'BV-Catalyst-Setup-Core' ]
]
