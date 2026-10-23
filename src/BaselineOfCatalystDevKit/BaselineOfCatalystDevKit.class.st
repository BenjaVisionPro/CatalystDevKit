Class {
	#name : 'BaselineOfCatalystDevKit',
	#superclass : 'BaselineOf',
	#category : 'BaselineOfCatalystDevKit',
	#package : 'BaselineOfCatalystDevKit'
}

{ #category : 'knowledge' }
BaselineOfCatalystDevKit class >> loadLepiter [
	| logicalDatabase |
	logicalDatabase := LeDatabasesRegistry defaultLogicalDatabase.
	{ 'CatalystDevKit' -> 'docs'. 'CatalystRuntime' -> 'lepiter' } do: [ :book |
		IceRepository registry
			detect: [ :repository | repository name = book key ]
			ifFound: [ :repository |
				| directory |
				directory := repository repositoryDirectory / book value.
				(directory / 'lepiter.properties') exists ifTrue: [
					logicalDatabase properties addRegisteredUrl: directory asLepiterZnUrl ] ]
			ifNone: [ ] ].
	logicalDatabase properties save.
	logicalDatabase reload
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> baseline: spec [
	<baseline>
	spec
		for: #common
		do: [ self coreBaselineOn: spec.
			self newArchitectureBaselineOn: spec.
			self legacyBaselineOn: spec ].

	^ spec
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> coreBaselineOn: spec [
	"I define the shared foundation packages and their DevKit integration."
	spec
		package: 'BV-Catalyst-Core';
		package: 'BV-Catalyst-DevKit-Core';
		package: 'BV-Catalyst-Fairy-Core'
			with: [ spec requires: #('BV-Catalyst-DevKit-Core') ]
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> ecosystemBaselineOn: spec [
	"I define the ecosystem packages layered over the simulator."
	spec
		package: 'BV-Catalyst-Ecosystem-Domain'
			with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

		package: 'BV-Catalyst-Ecosystem-Behaviours'
			with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Simulator-Core') ];

		package: 'BV-Catalyst-Ecosystem-Commands'
			with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Simulator-Commands' 'BV-Catalyst-Simulator-Core') ];

		package: 'BV-Catalyst-Ecosystem-Core'
			with: [ spec requires: #('BV-Catalyst-Ecosystem-Domain' 'BV-Catalyst-Ecosystem-Behaviours' 'BV-Catalyst-Ecosystem-Commands') ];

		package: 'BV-Catalyst-Ecosystem-ExamplesAndTests'
			with: [ spec requires: #('BV-Catalyst-Ecosystem-Core') ]
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> legacyBaselineOn: spec [
	"I keep the existing packages unchanged until migration is complete."
	spec
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

		package: 'BV-Catalyst-UE-Core';

		package: 'BV-Catalyst-Examples-Core';

		package: 'BV-Catalyst-Setup-Core';

		"Tests"
		package: 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
			with: [ spec requires: #('BV-Catalyst-Ecosystems-Sim-Core') ];

		package: 'BV-Catalyst-Tests-Connect-Core'
			with: [ spec requires: #('BV-Catalyst-Connect-Core') ];

		package: 'BV-Catalyst-Tests-Model-Universe-Core'
			with: [ spec requires: #('BV-Catalyst-Model-Universe-Core') ]
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> newArchitectureBaselineOn: spec [
	"I define the new Catalyst Runtime / Simulator / Ecosystem packages."

	self simulatorBaselineOn: spec.
	self ecosystemBaselineOn: spec
]

{ #category : 'baseline' }
BaselineOfCatalystDevKit >> simulatorBaselineOn: spec [
	"I define the simulator packages."
	spec
		package: 'BV-Catalyst-Simulator-Core';
		package: 'BV-Catalyst-Simulator-Commands'
			with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

		package: 'BV-Catalyst-Simulator-Routing'
			with: [ spec requires: #('BV-Catalyst-Simulator-Core') ];

		package: 'BV-Catalyst-Simulator-Pipeline'
			with: [ spec requires: #('BV-Catalyst-Simulator-Core' 'BV-Catalyst-Simulator-Commands' 'BV-Catalyst-Simulator-Routing') ];

		package: 'BV-Catalyst-Simulator-ExamplesAndTests'
			with: [ spec requires: #('BV-Catalyst-Simulator-Pipeline') ]
]
