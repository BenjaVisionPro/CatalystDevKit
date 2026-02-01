Class {
	#name : 'CRRuntimeConfigurationExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> devLocal [ 
	<gtExample>
	| cfg topology host deployment heartbeatDelivery heartbeatType heartbeatSchedule scheduler gateway sim playerView |

	cfg := CRRuntimeConfiguration new
		displayName: 'Dev Local';
		yourself.

	"Workers"
	heartbeatDelivery := CRWorkScheduleDeliveryConfiguration new
		overlapBehaviour: #skip;
		missedBehaviour: #skip;
		yourself.

	heartbeatType := CRIntervalWorkScheduleTypeConfiguration new
		intervalMillis: 2000;
		yourself.

	heartbeatSchedule := CRWorkScheduleConfiguration new
		identifier: #heartbeat;
		scheduleTypeConfiguration: heartbeatType;
		workUnitClassName: 'CRIdleWorkUnit';
		deliveryConfiguration: heartbeatDelivery;
		yourself.

	scheduler := CRWorkSchedulerConfiguration new
		schedules: { heartbeatSchedule };
		yourself.

	gateway := CRWorkerConfiguration new
		identifier: 'gateway';
		displayName: 'Client Gateway';
		workerClassName: 'CRWorker';
		schedulerConfiguration: scheduler;
		yourself.

	sim := CRWorkerConfiguration new
		identifier: 'simPartition';
		displayName: 'Simulation Partition';
		workerClassName: 'CRWorker';
		yourself.

	playerView := CRWorkerConfiguration new
		identifier: 'playerView';
		displayName: 'Player View';
		workerClassName: 'CRWorker';
		yourself.

	cfg workers: { gateway. sim. playerView }.

	"Topology"
	host := CRHostConfiguration new
		identifier: 'local';
		displayName: 'Local Host';
		address: 'localhost';
		maxProcesses: 6;
		workers: { 'gateway'. 'simPartition'. 'playerView' };
		yourself.

	topology := CRTopologyConfiguration new
		displayName: 'Local Topology';
		hosts: { host };
		placementStrategyConfiguration: CRRoundRobinPlacementStrategyConfiguration new;
		yourself.

	cfg topology: topology.

	"Deployment"
	deployment := CRRuntimeDeploymentConfiguration new
		workerDeployments: {
			(CRWorkerDeploymentConfiguration new workerIdentifier: 'gateway'; initialCount: 1; yourself).
			(CRWorkerDeploymentConfiguration new workerIdentifier: 'simPartition'; initialCount: 2; yourself).
			(CRWorkerDeploymentConfiguration new workerIdentifier: 'playerView'; initialCount: 1; yourself)
		};
		yourself.

	cfg deployment: deployment.

	^ cfg
]

{ #category : 'examples' }
CRRuntimeConfigurationExamples class >> testingLocal [
	<gtExample>
	| cfg host |
	cfg := self devLocal copy.	
	
	"More processes available"
	host := cfg topology hostConfigurationNamed: 'local'.
	host maxProcesses: 12.	
	
	"More workers deployed"
	(cfg deployment workerDeploymentForIdentifier: 'simPartition') initialCount: 6.
	(cfg deployment workerDeploymentForIdentifier: 'playerView') initialCount: 3.

	^ cfg
]
