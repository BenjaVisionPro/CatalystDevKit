Class {
	#name : 'CRWorkerServicesTests',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRWorkerServicesTests >> test_workerServicesAnswersCRServices [
	| worker |
	worker := CRWorker new.

	self assert: (worker services isKindOf: CRServices).
	self assert: worker services worker == worker
]

{ #category : 'tests' }
CRWorkerServicesTests >> test_workerServicesIsStableSameInstance [
	| worker s1 s2 |
	worker := CRWorker new.

	s1 := worker services.
	s2 := worker services.

	self assert: s1 == s2
]
