Class {
	#name : 'CRRuntimeConfigurationExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#tag : 'Examples'
}

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> allRuntimeConfigurations [
	"Keep this explicit. No clever reflection over <gtExample> methods."

	^ {self devLocal.
		self testingLocal}
]

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> devLocal [
	<gtExample>
	| cfg topology host deployment gatewayService simService viewService |
	cfg := CRRuntimeConfiguration new
			displayName: 'Dev Local';
			yourself.

	gatewayService := CRRuntimeServiceConfiguration new
			identifier: #playerGateway;
			displayName: 'Player Gateway';
			serviceClass: CRTestWorkerService;
			configuration: nil;
			yourself.

	simService := CRRuntimeServiceConfiguration new
			identifier: #simPartition;
			displayName: 'Simulation Partition';
			serviceClass: CRTestWorkerServiceB;
			configuration: nil;
			yourself.

	viewService := CRRuntimeServiceConfiguration new
			identifier: #playerView;
			displayName: 'Player View';
			serviceClass: CRTestWorkerServiceC;
			configuration: nil;
			yourself.

	cfg
		services: {gatewayService.
				simService.
				viewService} asOrderedCollection.
	cfg workers: #().	"Not required for service-first deployment."

	host := CRHostConfiguration new
			identifier: #local;
			displayName: 'Local Host';
			address: 'localhost';
			maxProcesses: 200;
			tags: {#local};
			workers: #();
			services: {#playerGateway.
					#simPartition.
					#playerView};
			yourself.

	topology := CRTopologyConfiguration new
			displayName: 'Local Topology';
			hosts: {host};
			placementStrategyConfiguration: CRRoundRobinPlacementStrategyConfiguration new;
			yourself.

	cfg topology: topology.

	deployment := CRRuntimeDeploymentConfiguration new
			serviceDeployments: {CRServiceDeploymentConfiguration new
						serviceIdentifier: #playerGateway;
						displayName: 'Gateway Instances';
						targetHostTags: {#local};
						initialCount: 1;
						yourself.
					CRServiceDeploymentConfiguration new
						serviceIdentifier: #simPartition;
						displayName: 'Sim Instances';
						targetHostTags: {#local};
						initialCount: 2;
						yourself.
					CRServiceDeploymentConfiguration new
						serviceIdentifier: #playerView;
						displayName: 'View Instances';
						targetHostTags: {#local};
						initialCount: 1;
						yourself} asOrderedCollection;
			yourself.

	cfg deployment: deployment.

	^ cfg
]

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> devLocalSTON [
	<gtExample>
	^ CRRuntimeConfigurationCodec toStringPretty: self devLocal
]

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> testingLocal [ 
	<gtExample>
	| cfg host |
	cfg := self devLocal copy.

	"More processes available"
	host := cfg topology hostConfigurationNamed: #local.
	host maxProcesses: 400.

	"More services deployed"
	(cfg deployment serviceDeployments detect: [ :each | each serviceIdentifier = #simPartition ])
		initialCount: 6.
	(cfg deployment serviceDeployments detect: [ :each | each serviceIdentifier = #playerView ])
		initialCount: 3.

	^ cfg
]
