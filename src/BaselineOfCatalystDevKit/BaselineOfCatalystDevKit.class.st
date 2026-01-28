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

				"==== New architecture packages (keep old ones until migration is complete) ===="

				"Runtime (CR*) - common, platform-neutral"
				package: 'BV-Catalyst-Runtime-Core'
					with: [ spec requires: #('BV-Catalyst-Core') ];

				"Runtime Examples/Tests remain self-contained, and must depend on the platform service"
				package: 'BV-Catalyst-Runtime-ExamplesAndTests'
					with: [ spec requires: #('BV-Catalyst-Runtime-Core') ];

				"Simulator (CS*)"
				package: 'BV-Catalyst-Simulator-Core'
					with: [ spec requires: #('BV-Catalyst-Runtime-Core') ];

				package: 'BV-Catalyst-Simulator-Commands'
					with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

				package: 'BV-Catalyst-Simulator-Routing'
					with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

				package: 'BV-Catalyst-Simulator-Pipeline'
					with: [ spec requires: #('BV-Catalyst-Simulator-Core' 'BV-Catalyst-Simulator-Commands' 'BV-Catalyst-Simulator-Routing') ];

				package: 'BV-Catalyst-Simulator-ExamplesAndTests'
					with: [ spec requires: #('BV-Catalyst-Simulator-Pipeline') ];

				"Ecosystem (CE*)"
				package: 'BV-Catalyst-Ecosystem-Domain'
					with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

				package: 'BV-Catalyst-Ecosystem-Behaviours'
					with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Simulator-Core') ];

				package: 'BV-Catalyst-Ecosystem-Commands'
					with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Simulator-Commands' 'BV-Catalyst-Simulator-Core') ];

				package: 'BV-Catalyst-Ecosystem-Core'
					with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Ecosystem-Behaviours' 'BV-Catalyst-Ecosystem-Commands') ];

				package: 'BV-Catalyst-Ecosystem-ExamplesAndTests'
					with: [ spec requires: #('BV-Catalyst-Ecosystem-Core') ];

				"==== Existing packages (unchanged for now) ===="

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

	"Platform-specific Runtime service implementations"
	spec
		for: #pharo
		do: [
			spec
				package: 'BV-Catalyst-Runtime-Service-Pharo'
					with: [ spec requires: #('BV-Catalyst-Runtime-Core') ].

			"Make runtime examples/tests depend on the Pharo service when loading on Pharo"
			spec
				group: 'runtime' with: #('BV-Catalyst-Runtime-Core' 'BV-Catalyst-Runtime-Server-Pharo');
				group: 'runtime-tests' with: #('BV-Catalyst-Runtime-ExamplesAndTests').

			spec
				package: 'BV-Catalyst-DevKit-Core'
		].

	spec
		for: #gemstone
		do: [
			spec
				package: 'BV-Catalyst-Runtime-Server-GemStone'
					with: [ spec requires: #('BV-Catalyst-Runtime-Core') ].

			"Make runtime examples/tests depend on the GemStone service when loading on GemStone"
			spec
				group: 'runtime' with: #('BV-Catalyst-Runtime-Core' 'BV-Catalyst-Runtime-Server-GemStone');
				group: 'runtime-tests' with: #('BV-Catalyst-Runtime-ExamplesAndTests')
		].

	^ spec
]
