Class {
	#name : 'CRTestWorkerService',
	#superclass : 'CRWorkerService',
	#instVars : [
		'installCount',
		'uninstallCount',
		'lastWorker',
		'lastConfiguration'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'accessing' }
CRTestWorkerService >> installCount [
	^ installCount ifNil: [ 0 ]
]

{ #category : 'lifecycle' }
CRTestWorkerService >> installOnWorker: aCRWorker configuration: aServiceConfiguration [
	installCount := self installCount + 1.
	lastWorker := aCRWorker.
	lastConfiguration := aServiceConfiguration.
	^ self
]

{ #category : 'accessing' }
CRTestWorkerService >> lastConfiguration [
	^ lastConfiguration
]

{ #category : 'accessing' }
CRTestWorkerService >> lastWorker [
	^ lastWorker
]

{ #category : 'accessing' }
CRTestWorkerService >> uninstallCount [
	^ uninstallCount ifNil: [ 0 ]
]

{ #category : 'lifecycle' }
CRTestWorkerService >> uninstallFromWorker: aCRWorker [
	uninstallCount := self uninstallCount + 1.
	^ self
]
