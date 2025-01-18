Class {
	#name : #BaselineOfCatalystDevKit,
	#superclass : #BaselineOf,
	#category : #BaselineOfCatalystDevKit
}

{ #category : #knowledge }
BaselineOfCatalystDevKit class >> loadLepiter [
	IceRepository registry  
		detect: [ :aRepository |
			aRepository name = 'CatalystDevKit' ]
		ifFound: [ :aRepository | 
			| defaultDatabase currentProperties |
			defaultDatabase := LeDatabasesRegistry defaultLogicalDatabase.
			currentProperties := defaultDatabase properties.
			currentProperties addRegisteredDirectory: aRepository repositoryDirectory / 'docs'.
			defaultDatabase reload ]
		ifNone: [
			self inform: 'Repository not found.' ]
]

{ #category : #baseline }
BaselineOfCatalystDevKit >> baseline: spec [
	<baseline>
	spec
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
				package: 'BV-Catalyst-Setup-Core';
				package: 'BV-Catalyst-Model-Universe-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];
				package: 'BV-Catalyst-ACF-Core' ].
	spec for: #pharo do: [ spec package: 'BV-Catalyst-DevKit-Core' ].
	^ spec
]
