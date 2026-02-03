Class {
	#name : 'CRServices',
	#superclass : 'Object',
	#instVars : [
		'worker',
		'byClass'
	],
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'instance creation' }
CRServices class >> onWorker: aCRWorker [
	^ self new
		worker: aCRWorker;
		yourself
]

{ #category : 'testing' }
CRServices >> hasAnyServices [
	^ byClass isEmpty not
]

{ #category : 'testing' }
CRServices >> hasServiceClass: aServiceClass [
	^ byClass includesKey: aServiceClass
]

{ #category : 'initialization' }
CRServices >> initialize [
	super initialize.
	byClass := Dictionary new
]

{ #category : 'lifecycle' }
CRServices >> installServiceClass: aServiceClass configuration: aServiceConfiguration [
	| existing service |
	aServiceClass isClass
		ifFalse: [ (CRInvalidWorkerServiceClassException worker: worker given: aServiceClass)
				signal ].

	existing := byClass at: aServiceClass ifAbsent: [ nil ].
	existing
		ifNotNil: [ (CRDuplicateWorkerServiceException worker: worker serviceClass: aServiceClass)
				signal ].

	(aServiceClass inheritsFrom: CRWorkerService)
		ifFalse: [ (CRInvalidWorkerServiceImplementationException
				worker: worker
				serviceClass: aServiceClass) signal ].

	service := aServiceClass new.
	service installOnWorker: worker configuration: aServiceConfiguration.
	byClass at: aServiceClass put: service.
	^ service
]

{ #category : 'accessing' }
CRServices >> installedServiceClasses [
	^ byClass keys asArray
]

{ #category : 'accessing' }
CRServices >> service: aServiceClass requiredByWorkUnitClass: aWorkUnitClass [
	| service |
	service := byClass at: aServiceClass ifAbsent: [ nil ].
	service
		ifNil: [ (CRMissingWorkerServiceException
				worker: worker
				serviceClass: aServiceClass
				workUnitClass: aWorkUnitClass) signal ].
	^ service
]

{ #category : 'accessing' }
CRServices >> serviceOrNil: aServiceClass [
	^ byClass at: aServiceClass ifAbsent: [ nil ]
]

{ #category : 'lifecycle' }
CRServices >> uninstallAll [
	| all |
	byClass ifNil: [ ^ self ].

	all := byClass values asArray.

	all
		do: [ :each | [ each uninstallFromWorker: worker ] on: Error do: [ :ex | nil ] ].

	byClass removeAll
]

{ #category : 'accessing' }
CRServices >> worker [
	^ worker
]

{ #category : 'accessing' }
CRServices >> worker: anObject [
	worker := anObject
]
