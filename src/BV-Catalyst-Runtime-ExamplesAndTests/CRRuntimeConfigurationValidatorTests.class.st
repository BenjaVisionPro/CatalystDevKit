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
CRRuntimeConfigurationValidatorTests >> assertValid: aCRRuntimeConfiguration [ 
	| result |
	result := aCRRuntimeConfiguration validate.
	self assert: result isValid.
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_deploymentReferencesUnknownWorkerIsError [
	| cfg dep result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	dep := cfg deployment workerDeployments copy.
	dep
		add: (CRWorkerDeploymentConfiguration new
				workerIdentifier: 'ghostWorker';
				initialCount: 1;
				yourself).
	cfg deployment workerDeployments: dep.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e includesSubstring: 'Deployment references unknown workerIdentifier' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_duplicateScheduleIdentifierOnWorkerIsError [
	| cfg worker sched schedule1 schedule2 result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	worker := cfg workerConfigurationNamed: 'gateway'.
	sched := worker schedulerConfiguration.

	schedule1 := sched schedules first.
	schedule2 := CRWorkScheduleConfiguration new
			identifier: schedule1 identifier;
			scheduleTypeConfiguration: (CRIntervalWorkScheduleTypeConfiguration new
					intervalMillis: 2000;
					yourself);
			workUnitClassName: 'CRIdleWorkUnit';
			deliveryConfiguration: (CRWorkScheduleDeliveryConfiguration new
					overlapBehaviour: #skip;
					missedBehaviour: #skip;
					yourself);
			yourself.

	sched schedules: sched schedules , {schedule2}.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e includesSubstring: 'Duplicate schedule identifier' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_duplicateWorkerIdentifierIsError [
	| cfg w1 w2 result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	w1 := CRWorkerConfiguration new
			identifier: 'dup';
			displayName: 'A';
			workerClassName: 'CRWorker';
			yourself.
	w2 := CRWorkerConfiguration new
			identifier: 'dup';
			displayName: 'B';
			workerClassName: 'CRWorker';
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
CRRuntimeConfigurationValidatorTests >> test_hostReferencesUnknownWorkerIsError [
	| cfg host result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	host := cfg topology hostConfigurationNamed: 'local'.
	host workers: host workers , {'ghostWorker'}.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e includesSubstring: 'references unknown worker' ])
]

{ #category : 'tests' }
CRRuntimeConfigurationValidatorTests >> test_intervalScheduleRequiresPositiveIntervalMillis [
	| cfg worker sched scheduleType schedule result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	worker := cfg workerConfigurationNamed: 'gateway'.
	sched := worker schedulerConfiguration.

	scheduleType := CRIntervalWorkScheduleTypeConfiguration new
			intervalMillis: 0;
			yourself.

	schedule := CRWorkScheduleConfiguration new
			identifier: #badHeartbeat;
			scheduleTypeConfiguration: scheduleType;
			workUnitClassName: 'CRIdleWorkUnit';
			deliveryConfiguration: (CRWorkScheduleDeliveryConfiguration new
					overlapBehaviour: #skip;
					missedBehaviour: #skip;
					yourself);
			yourself.

	sched schedules: sched schedules , {schedule}.

	result := self assertInvalid: cfg.
	self
		assert: (result errors anySatisfy: [ :e | e includesSubstring: 'intervalMillis > 0' ])
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
	| cfg d scale result |
	cfg := CRRuntimeConfigurationExamples devLocal.

	d := cfg deployment workerDeploymentForIdentifier: 'simPartition'.

	scale := CRScaleConfiguration new.
	scale minCount: 5.
	scale maxCount: 2.	"invalid"
	d scaleConfiguration: scale.

	result := self assertInvalid: cfg.
	self
		assert: (result errors
				anySatisfy: [ :e | e includesSubstring: 'maxCount must be >= minCount' ])
]
