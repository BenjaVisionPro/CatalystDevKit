Class {
	#name : 'CRTestWorkerServiceB',
	#superclass : 'CRWorkerService',
	#instVars : [
		'installCount',
		'uninstallCount'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'accessing' }
CRTestWorkerServiceB >> installCount [
	^ installCount ifNil: [ 0 ]
]

{ #category : 'lifecycle' }
CRTestWorkerServiceB >> installOnWorker: aCRWorker configuration: aServiceConfiguration [ 
	installCount := self installCount + 1.
	^ self
]

{ #category : 'accessing' }
CRTestWorkerServiceB >> uninstallCount [
	^ uninstallCount ifNil: [ 0 ]
]

{ #category : 'lifecycle' }
CRTestWorkerServiceB >> uninstallFromWorker: aCRWorker [
	uninstallCount := self uninstallCount + 1
]
