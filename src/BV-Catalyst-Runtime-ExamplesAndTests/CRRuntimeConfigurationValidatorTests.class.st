Class {
	#name : 'CRRuntimeConfigurationValidatorTests',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'helpers' }
CRRuntimeConfigurationValidatorTests >> assertInvalid: aCRRuntimeConfiguration [
	| result |
	result := aCRRuntimeConfiguration validate.
	self deny: result isValid.
	^ result
]

{ #category : 'helpers' }
CRRuntimeConfigurationValidatorTests >> assertInvalid: aCRRuntimeConfiguration withErrorContaining: aSubstring [
	| result |
	result := self validationResultFor: aCRRuntimeConfiguration.
	self deny: result isValid.
	self
		assert: (result errors
				anySatisfy: [ :each | each asString includesSubstring: aSubstring ]).
	^ result
]

{ #category : 'helpers' }
CRRuntimeConfigurationValidatorTests >> assertValid: aCRRuntimeConfiguration [ 
	| result |
	result := aCRRuntimeConfiguration validate.
	self assert: result isValid.
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_deploymentReferencesUnknownServiceIsError [
	| cfg dep result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	dep := cfg deployment serviceDeployments copy.
	dep
		add: (CRServiceDeploymentConfiguration new
				serviceIdentifier: #ghostServiceIdentifier;
				initialCount: 1;
				yourself).
	cfg deployment serviceDeployments: dep.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'references unknown service' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_deploymentServiceIdentifierMustBeSymbol [
	| cfg dep result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	dep := cfg deployment serviceDeployments
			detect: [ :each | each serviceIdentifier = #simPartition ]
			ifNone: [ self fail: 'devLocal must include service deployment #simPartition.' ].

	dep serviceIdentifier: 'simPartition'.	"String on purpose"

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | 
					(e includesSubstring: 'serviceIdentifier')
						and: [ e includesSubstring: 'must be a Symbol' ] ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_devExample_stonContainsSymbolIdentifiers [
	| ston |
	ston := STON toStringPretty: CRRuntimeConfigurationExamples devLocal.
	self assert: (ston includesSubstring: '#playerGateway').
	self assert: (ston includesSubstring: '#local').
	self assert: (ston includesSubstring: '#simPartition')
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_duplicateScheduleIdentifierOnWorkerIsError [
	| cfg worker sched schedule1 schedule2 result |

	cfg := CRRuntimeConfigurationExamples devLocal.

	"Build a worker configuration just for this test."
	schedule1 := CRWorkScheduleConfiguration new
		identifier: #heartbeat;
		scheduleTypeConfiguration: (CRIntervalWorkScheduleTypeConfiguration new
			intervalMillis: 2000;
			yourself);
		workUnitClass: #CRIdleWorkUnit;
		deliveryConfiguration: (CRWorkScheduleDeliveryConfiguration new
			overlapBehaviour: #skip;
			missedBehaviour: #skip;
			yourself);
		yourself.

	schedule2 := CRWorkScheduleConfiguration new
		identifier: #heartbeat; "duplicate on purpose"
		scheduleTypeConfiguration: (CRIntervalWorkScheduleTypeConfiguration new
			intervalMillis: 2000;
			yourself);
		workUnitClass: #CRIdleWorkUnit;
		deliveryConfiguration: (CRWorkScheduleDeliveryConfiguration new
			overlapBehaviour: #skip;
			missedBehaviour: #skip;
			yourself);
		yourself.

	sched := CRWorkSchedulerConfiguration new
		schedules: { schedule1. schedule2 };
		yourself.

	worker := CRWorkerConfiguration new
		identifier: #gateway;
		displayName: 'Gateway Worker';
		workerClass: #CRWorker;
		schedulerConfiguration: sched;
		yourself.

	cfg workers: (cfg workers copyWith: worker).

	result := self assertInvalid: cfg.
	self assert: (result errors anySatisfy: [ :e |
		e asString includesSubstring: 'duplicate schedule identifier' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_duplicateWorkerIdentifierIsError [
	| cfg w1 w2 result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	w1 := CRWorkerConfiguration new
			identifier: 'dup';
			displayName: 'A';
			workerClass: 'CRWorker';
			yourself.
	w2 := CRWorkerConfiguration new
			identifier: 'dup';
			displayName: 'B';
			workerClass: 'CRWorker';
			yourself.
	cfg
		workers: cfg workers
				, {w1.
						w2}.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e includesSubstring: 'Duplicate worker identifier' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_exampleDevLocalIsValid [
	self assertValid: CRRuntimeConfigurationExamples devLocal
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_hostIdentifierMustBeSymbol [
	| cfg host |
	cfg := CRRuntimeConfigurationExamples devLocal.
	host := cfg topology hostConfigurationNamed: #local.
	host identifier: 'local'.
	self
		assertInvalid: cfg
		withErrorContaining: 'Host identifier must be a Symbol'
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_hostReferencesUnknownServiceIsError [ 
	| cfg host result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	host := cfg topology hostConfigurationNamed: #local.
	host services: host services , { #ghostService }.

	result := self assertInvalid: cfg.
	self assert: (result errors anySatisfy: [ :e |
		e asString includesSubstring: 'references unknown service' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_hostReferencesUnknownWorkerIsError [
	| cfg host result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	host := cfg topology hostConfigurationNamed: #local.
	host workers: host workers , {#ghostWorker}.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'references unknown worker' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_intervalScheduleRequiresPositiveIntervalMillis [
	| result scheduleType |
	result := CRRuntimeConfigurationValidationResult new.

	scheduleType := CRIntervalWorkScheduleTypeConfiguration new
			intervalMillis: 0;
			yourself.

	scheduleType
		validateOn: result
		forWorkerIdentifier: #gateway
		scheduleIdentifier: #badHeartbeat.

	self deny: result isValid.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'intervalMillis must be a positive Integer' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_missingPlacementStrategyIsError [
	| cfg result |
	cfg := CRRuntimeConfigurationExamples devLocal.
	cfg topology placementStrategyConfiguration: nil.
	result := self assertInvalid: cfg.
	self
		assert: (result errors anySatisfy: [ :e | e includesSubstring: 'placement strategy' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_missingTopologyIsError [
	| cfg result |
	cfg := CRRuntimeConfigurationExamples devLocal.
	cfg topology: nil.
	result := self assertInvalid: cfg.
	self
		assert: (result errors anySatisfy: [ :e | e includesSubstring: 'must specify topology' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_scaleConfigurationRangeChecks [
	| cfg dep scale result |
	cfg := CRRuntimeConfigurationExamples devLocal.	"Make this test independent of devLocal’s contents."
	dep := CRServiceDeploymentConfiguration new
			serviceIdentifier: #simPartition;
			displayName: 'Sim Partitions';
			targetHostTags: {#local};
			initialCount: 1;
			yourself.

	scale := CRScaleConfiguration new.
	scale minCount: 5.
	scale maxCount: 2.	"invalid"
	dep scaleConfiguration: scale.

	cfg deployment
		serviceDeployments: (cfg deployment serviceDeployments copyWith: dep).

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | (e includesSubstring: 'maxCount') and: [ e includesSubstring: 'minCount' ] ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_scheduleIdentifierMustBeSymbol [
	| cfg worker sched schedule result |
	cfg := CRRuntimeConfigurationExamples devLocal.	"Build the minimum worker config needed for this test (no dependency on devLocal contents)."
	schedule := CRWorkScheduleConfiguration new
			identifier: #heartbeat;
			scheduleTypeConfiguration: (CRIntervalWorkScheduleTypeConfiguration new
					intervalMillis: 2000;
					yourself);
			workUnitClass: #CRIdleWorkUnit;
			deliveryConfiguration: (CRWorkScheduleDeliveryConfiguration new
					overlapBehaviour: #skip;
					missedBehaviour: #skip;
					yourself);
			yourself.

	sched := CRWorkSchedulerConfiguration new
			schedules: {schedule};
			yourself.

	worker := CRWorkerConfiguration new
			identifier: #gateway;
			displayName: 'Gateway Worker';
			workerClass: #CRWorker;
			schedulerConfiguration: sched;
			yourself.

	cfg workers: (cfg workers copyWith: worker).	"Now break it on purpose."
	schedule identifier: 'heartbeat'.	"String on purpose"

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'schedule identifier must be a Symbol' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_serviceDeploymentIdentifierMustBeSymbol [
	| cfg dep result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	dep := CRServiceDeploymentConfiguration new
			serviceIdentifier: 'simPartition';
			displayName: 'Sim Partitions';
			targetHostTags: {#local};
			initialCount: 1;
			yourself.	"String on purpose"

	cfg deployment
		serviceDeployments: (cfg deployment serviceDeployments copyWith: dep).

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | 
					(e includesSubstring: 'serviceIdentifier')
						and: [ e includesSubstring: 'must be a Symbol' ] ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_serviceDeploymentReferencesUnknownServiceIsError [
	| cfg dep result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	dep := cfg deployment serviceDeployments copy.
	dep
		add: (CRServiceDeploymentConfiguration new
				serviceIdentifier: #ghostService;
				displayName: 'Ghost';
				targetHostTags: {#local};
				initialCount: 1;
				yourself).
	cfg deployment serviceDeployments: dep.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'Service deployment references unknown service' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_serviceIdentifierMustBeSymbol [
	| cfg service |
	cfg := CRRuntimeConfigurationExamples devLocal.

	service := cfg services first.
	service identifier: 'playerGateway'.	"String on purpose"

	self
		assertInvalid: cfg
		withErrorContaining: 'Service identifier must be a Symbol'
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_workerIdentifierMustBeSymbol [
	| cfg worker result |
	cfg := CRRuntimeConfigurationExamples devLocal.
	worker := CRWorkerConfiguration new
			identifier: #gateway;
			displayName: 'Gateway Worker';
			workerClass: #CRWorker;
			yourself.

	cfg workers: (cfg workers copyWith: worker).	"Break it on purpose."
	worker identifier: 'gateway'.	"String on purpose"

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e asString includesSubstring: 'Worker identifier must be a Symbol' ])
]

{ #category : 'helpers' }
CRRuntimeConfigurationValidatorTests >> validationErrorsFor: aRuntimeConfiguration [
	^ aRuntimeConfiguration validate errors
]

{ #category : 'helpers' }
CRRuntimeConfigurationValidatorTests >> validationResultFor: aCRRuntimeConfiguration [
	^ aCRRuntimeConfiguration validate
]
