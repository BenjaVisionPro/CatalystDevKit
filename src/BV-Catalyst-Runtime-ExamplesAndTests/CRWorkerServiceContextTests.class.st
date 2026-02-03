Class {
	#name : 'CRWorkerServiceContextTests',
	#superclass : 'CRAbstractWorkerTests',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRWorkerServiceContextTests >> test_missingRequiredServiceAnnouncesFailureAndWorkerContinues [
	self
		withRunningWorkerDo: [ :worker :host | 
			| failures continued |
			failures := OrderedCollection new.
			continued := false.

			worker announcer
				when: CRWorkUnitFailedAnnouncement
				do: [ :ann | failures add: ann ]
				for: self.	
				
			"1) This unit requires CRTestWorkerService, but we did not install it."
			worker enqueue: CRTestRequiresWorkerServiceWorkUnit new.	
			
			"2) This must still run."
			worker enqueue: (CRBlockUnit on: [ continued := true ]).

			self
				waitUntil: [ failures notEmpty ]
				upToMSecs: 500
				description: 'waiting for failure announcement for missing required worker service.'.

			self
				waitUntil: [ continued ]
				upToMSecs: 500
				description: 'waiting for worker to continue after missing service failure.'.

			self assert: failures size equals: 1 ]
]

{ #category : 'tests' }
CRWorkerServiceContextTests >> test_requiredServiceIsProvidedInContextWhenInstalled [
	self
		withRunningWorkerDo: [ :worker :host | 
			| unit done installedService |
			"Install service explicitly (no config wiring yet)."
			installedService := worker services
					installServiceClass: CRTestWorkerService
					configuration: nil.

			done := Semaphore new.
			unit := CRTestRequiresWorkerServiceWorkUnit new.
			unit doneSemaphore: done.

			worker enqueue: unit.

			self
				waitUntil: [ done waitTimeoutMilliseconds: 200 ]
				upToMSecs: 500
				description: 'waiting for CRTestRequiresWorkerServiceWorkUnit to run.'.

			self assert: unit observedWorker == worker.
			self assert: unit observedServices == worker services.
			self assert: unit observedService == installedService ]
]

{ #category : 'tests' }
CRWorkerServiceContextTests >> test_workUnitReceivesExecutionContext [
	self
		withRunningWorkerDo: [ :worker :host | 
			| unit done |
			done := Semaphore new.
			unit := CRTestContextCapturingWorkUnit new.
			unit doneSemaphore: done.

			worker enqueue: unit.

			self
				waitUntil: [ done waitTimeoutMilliseconds: 200 ]
				upToMSecs: 500
				description: 'waiting for CRTestContextCapturingWorkUnit to run and capture context.'.

			self assert: unit capturedContext notNil.
			self assert: unit capturedContext worker == worker.
			self assert: unit capturedContext services == worker services ]
]
