Class {
	#name : 'CRWorkScheduleConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'scheduleTypeConfiguration',
		'deliveryConfiguration',
		'workUnitClass'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> deliveryConfiguration [
	^ deliveryConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> deliveryConfiguration: aCRWorkScheduleDeliveryConfiguration [
	deliveryConfiguration := aCRWorkScheduleDeliveryConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> identifier [
	^ identifier
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> identifier: aSymbol [
	identifier := aSymbol
]

{ #category : 'initialization' }
CRWorkScheduleConfiguration >> initialize [
	super initialize.
	identifier := nil.
	scheduleTypeConfiguration := nil.
	workUnitClass := ''.
	deliveryConfiguration := nil
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> scheduleTypeConfiguration [
	^ scheduleTypeConfiguration
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> scheduleTypeConfiguration: aCRWorkScheduleTypeConfiguration [
	scheduleTypeConfiguration := aCRWorkScheduleTypeConfiguration
]

{ #category : 'validation' }
CRWorkScheduleConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier [
	| workerLabel scheduleLabel |
	workerLabel := aWorkerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ aWorkerIdentifier printString ].

	scheduleLabel := identifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ identifier printString ].

	identifier isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule identifier is required.' ]
		ifFalse: [ identifier isSymbol
				ifFalse: [ aValidationResult
						addError: 'Worker ' , workerLabel , ' schedule identifier must be a Symbol; got '
								, identifier printString , ' (' , identifier class name , ').' ] ].

	scheduleTypeConfiguration isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' must specify schedule type configuration.' ]
		ifFalse: [ scheduleTypeConfiguration
				validateOn: aValidationResult
				forWorkerIdentifier: aWorkerIdentifier
				scheduleIdentifier: identifier ].

	workUnitClass isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' must specify workUnitClass.' ]
		ifFalse: [ workUnitClass isSymbol
				ifFalse: [ aValidationResult
						addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
								, ' workUnitClass must be a Symbol; got ' , workUnitClass printString
								, ' (' , workUnitClass class name , ').' ] ].

	deliveryConfiguration isNil
		ifTrue: [ aValidationResult
				addError: 'Worker ' , workerLabel , ' schedule ' , scheduleLabel
						, ' must specify delivery configuration.' ]
		ifFalse: [ deliveryConfiguration
				validateOn: aValidationResult
				forWorkerIdentifier: aWorkerIdentifier
				scheduleIdentifier: identifier ]
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClass [
	^ workUnitClass
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClass: aSymbol [
	workUnitClass := aSymbol
]
