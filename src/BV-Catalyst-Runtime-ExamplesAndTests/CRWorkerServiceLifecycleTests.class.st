Class {
	#name : 'CRWorkerServiceLifecycleTests',
	#superclass : 'CRAbstractWorkerTests',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesInstalledOnStartFromServiceConfigurations [
	| worker host cfg |
	worker := self newWorker.

	cfg := CRWorkerServiceConfiguration new
			serviceClass: CRTestWorkerService;
			configuration: nil;
			yourself.

	worker serviceConfigurations: {cfg} asOrderedCollection.

	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.
	[ self assert: (worker services hasServiceClass: CRTestWorkerService) ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesUninstalledEvenIfAUnitFails [
	| worker host cfg service |
	worker := self newWorker.

	cfg := CRWorkerServiceConfiguration new
			serviceClass: CRTestWorkerService;
			configuration: nil;
			yourself.

	worker serviceConfigurations: {cfg} asOrderedCollection.

	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.
	[ service := worker services
			service: CRTestWorkerService
			requiredByWorkUnitClass: self class.

	worker enqueue: (CRBlockUnit on: [ Error signal: 'boom' ]).

	self
		waitUntil: [ service installCount = 1 ]
		upToMSecs: 500
		description: 'waiting for service install.'.

	worker stop.
	host ensureStoppedUpToMSecs: self stopTimeoutMSecs.

	self assert: service uninstallCount equals: 1 ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesUninstalledOnStop [
	| worker host cfg service |
	worker := self newWorker.

	cfg := CRWorkerServiceConfiguration new
			serviceClass: CRTestWorkerService;
			configuration: nil;
			yourself.

	worker serviceConfigurations: {cfg} asOrderedCollection.

	host := self startWorker: worker andWaitUpToMSecs: self startTimeoutMSecs.
	[ service := worker services
			service: CRTestWorkerService
			requiredByWorkUnitClass: self class.

	worker stop.
	host ensureStoppedUpToMSecs: self stopTimeoutMSecs.

	self assert: service uninstallCount equals: 1.
	self deny: (worker services hasServiceClass: CRTestWorkerService) ]
		ensure: [ host ensureStoppedUpToMSecs: self stopTimeoutMSecs ]
]
