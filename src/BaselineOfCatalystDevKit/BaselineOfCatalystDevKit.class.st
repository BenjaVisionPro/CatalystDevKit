Class {
	#name : 'BaselineOfCatalystDevKit',
	#superclass : 'BaselineOf',
	#category : 'BaselineOfCatalystDevKit',
	#package : 'BaselineOfCatalystDevKit'
}

{ #category : 'knowledge' }
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

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> baseline: spec [
	<baseline>
	spec
		for: #common
		do: [
			spec
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

				package: 'BV-Catalyst-Model-Universe-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];

				package: 'BV-Catalyst-Ecosystems-Sim-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];

				package: 'BV-Catalyst-Ecosystems-Sim-Commands-Core'
					with: [ spec requires: #('BV-Catalyst-Ecosystems-Sim-Core') ];

				package: 'BV-Catalyst-Ecosystems-Sim-Operations-Core'
					with: [ spec requires: #('BV-Catalyst-Ecosystems-Sim-Core') ];

				package: 'BV-Catalyst-Fairy-Core'
					with: [ spec requires: #('BV-Catalyst-Store-Core') ];

				package: 'BV-Catalyst-Fairy-Events'
					with: [ spec requires: #('BV-Catalyst-Fairy-Core') ];

				package: 'BV-Catalyst-UE-Core';

				package: 'BV-Catalyst-Examples-Core';

				package: 'BV-Catalyst-Setup-Core';

				"Tests"
				package: 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
					with: [ spec requires: #('BV-Catalyst-Ecosystems-Sim-Core') ];

				package: 'BV-Catalyst-Tests-Connect-Core'
					with: [ spec requires: #('BV-Catalyst-Connect-Core') ];

				package: 'BV-Catalyst-Tests-Model-Universe-Core'
					with: [ spec requires: #('BV-Catalyst-Model-Universe-Core') ].
		].

	spec
		for: #pharo
		do: [
			spec
				package: 'BV-Catalyst-DevKit-Core'
		].

	^ spec
]
