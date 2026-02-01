Class {
	#name : 'CRWorkScheduleConfiguration',
	#superclass : 'Object',
	#instVars : [
		'identifier',
		'scheduleTypeConfiguration',
		'workUnitClassName',
		'deliveryConfiguration'
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
	workUnitClassName := ''.
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
CRWorkScheduleConfiguration >> validateOn: result forWorkerIdentifier: workerIdentifier [
	| workerLabel |
	workerLabel := workerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ workerIdentifier printString ].

	identifier isNil
		ifTrue: [ result addError: 'Worker ' , workerLabel , ' schedule identifier is required.' ]
		ifFalse: [ identifier isSymbol
				ifFalse: [ result
						addError: 'Worker ' , workerLabel , ' schedule identifier must be a Symbol; got '
								, identifier printString , ' (' , identifier class name , ').' ] ].

	scheduleTypeConfiguration isNil
		ifTrue: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , identifier printString
						, ' must specify schedule type configuration.' ]
		ifFalse: [ scheduleTypeConfiguration
				validateOn: result
				forWorkerIdentifier: workerIdentifier
				scheduleIdentifier: identifier ].

	(workUnitClassName isNil or: [ workUnitClassName asString isEmpty ])
		ifTrue: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , identifier printString
						, ' must specify workUnitClassName.' ].

	deliveryConfiguration isNil
		ifTrue: [ result
				addError: 'Worker ' , workerLabel , ' schedule ' , identifier printString
						, ' must specify delivery configuration.' ]
		ifFalse: [ deliveryConfiguration
				validateOn: result
				forWorkerIdentifier: workerIdentifier
				scheduleIdentifier: identifier ]
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClassName [
	^ workUnitClassName
]

{ #category : 'accessing' }
CRWorkScheduleConfiguration >> workUnitClassName: aString [
	workUnitClassName := aString asString
]
