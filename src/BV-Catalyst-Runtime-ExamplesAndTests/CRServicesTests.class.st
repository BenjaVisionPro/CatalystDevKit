Class {
	#name : 'CRServicesTests',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRServicesTests >> test_duplicateInstallRaises [
	| worker services |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	services installServiceClass: CRTestWorkerService configuration: nil.

	self
		should: [ services installServiceClass: CRTestWorkerService configuration: nil ]
		raise: CRDuplicateWorkerServiceException
]

{ #category : 'tests' }
CRServicesTests >> test_installAndLookupReturnsInstalledInstance [
	| worker services installed lookedUp |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	installed := services
			installServiceClass: CRTestWorkerService
			configuration: nil.

	lookedUp := services
			service: CRTestWorkerService
			requiredByWorkUnitClass: CRBlockUnit.

	self assert: installed == lookedUp.
	self assert: installed installCount equals: 1.
	self assert: installed lastWorker == worker.
	self assert: (services hasServiceClass: CRTestWorkerService)
]

{ #category : 'tests' }
CRServicesTests >> test_installRejectsClassNotInheritingCRWorkerService [
	| worker services |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	self
		should: [ services installServiceClass: Object configuration: nil ]
		raise: CRInvalidWorkerServiceImplementationException
]

{ #category : 'tests' }
CRServicesTests >> test_installRejectsNonClass [
	| worker services |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	self
		should: [ services installServiceClass: 42 configuration: nil ]
		raise: CRInvalidWorkerServiceClassException
]

{ #category : 'tests' }
CRServicesTests >> test_missingServiceLookupRaises [
	| worker services |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	self
		should: [ services service: CRTestWorkerService requiredByWorkUnitClass: CRBlockUnit ]
		raise: CRMissingWorkerServiceException
]

{ #category : 'tests' }
CRServicesTests >> test_uninstallAllCallsUninstallHookAndClearsRegistry [
	| worker services a b |
	worker := CRWorker new.
	services := CRServices onWorker: worker.

	a := services installServiceClass: CRTestWorkerService configuration: nil.
	b := services installServiceClass: CRTestWorkerServiceB configuration: nil.

	self assert: a uninstallCount equals: 0.
	self assert: b uninstallCount equals: 0.

	services uninstallAll.

	self assert: a uninstallCount equals: 1.
	self assert: b uninstallCount equals: 1.
	self deny: (services hasServiceClass: CRTestWorkerService).
	self deny: (services hasServiceClass: CRTestWorkerServiceB).
	self assert: services installedServiceClasses isEmpty
]
