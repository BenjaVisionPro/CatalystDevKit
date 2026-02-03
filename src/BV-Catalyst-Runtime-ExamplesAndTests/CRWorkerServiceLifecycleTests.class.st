Class {
	#name : 'CRWorkerServiceLifecycleTests',
	#superclass : 'CRAbstractWorkerTests',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesInstalledOnStartFromServiceConfigurations [
	self
		withRunningWorkerDo: [ :worker :host | 
			| cfg |
			cfg := CRWorkerServiceConfiguration new
					identifier: #testService;
					serviceClass: CRTestWorkerService;
					configuration: nil;
					yourself.

			worker stop.	"we need to restart with configs applied"
			worker serviceConfigurations: {cfg} asOrderedCollection.
			host startWorker: worker.

			self assert: (worker services hasServiceClass: CRTestWorkerService) ]
]

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesUninstalledEvenIfAUnitFails [
	self
		withRunningWorkerDo: [ :worker :host | 
			| cfg service |
			cfg := CRWorkerServiceConfiguration new
					identifier: #testService;
					serviceClass: CRTestWorkerService;
					configuration: nil;
					yourself.

			worker stop.
			worker serviceConfigurations: {cfg} asOrderedCollection.
			host startWorker: worker.

			service := worker services
					service: CRTestWorkerService
					requiredByWorkUnitClass: self class.

			worker enqueue: (CRBlockUnit on: [ Error signal: 'boom' ]).

			self
				waitUntil: [ service installCount = 1 ]
				upToMSecs: 500
				description: 'waiting for service install.'.

			worker stop.
			host waitForWorkerToStop: worker.

			self assert: service uninstallCount equals: 1 ]
]

{ #category : 'tests' }
CRWorkerServiceLifecycleTests >> test_servicesUninstalledOnStop [
	self
		withRunningWorkerDo: [ :worker :host | 
			| cfg service |
			cfg := CRWorkerServiceConfiguration new
					identifier: #testService;
					serviceClass: CRTestWorkerService;
					configuration: nil;
					yourself.

			worker stop.
			worker serviceConfigurations: {cfg} asOrderedCollection.
			host startWorker: worker.

			service := worker services
					service: CRTestWorkerService
					requiredByWorkUnitClass: self class.

			worker stop.
			host waitForWorkerToStop: worker.

			self assert: service uninstallCount equals: 1.
			self deny: (worker services hasServiceClass: CRTestWorkerService) ]
]
