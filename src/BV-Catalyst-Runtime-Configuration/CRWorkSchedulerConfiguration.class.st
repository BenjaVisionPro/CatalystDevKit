Class {
	#name : 'CRWorkSchedulerConfiguration',
	#superclass : 'Object',
	#instVars : [
		'schedules'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'initialization' }
CRWorkSchedulerConfiguration >> initialize [
	super initialize.
	schedules := OrderedCollection new
]

{ #category : 'accessing' }
CRWorkSchedulerConfiguration >> schedules [
	^ schedules
]

{ #category : 'accessing' }
CRWorkSchedulerConfiguration >> schedules: aCollection [
	schedules := aCollection asOrderedCollection
]

{ #category : 'validation' }
CRWorkSchedulerConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier [
	| ids |
	ids := Set new.
	schedules do: [ :each | 
		each validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier.
		(each identifier isNil or: [ each identifier asString isEmpty ]) ifFalse: [
			(ids includes: each identifier asString)
				ifTrue: [ aValidationResult addError: 'Duplicate schedule identifier ', each identifier printString, ' on worker ', aWorkerIdentifier printString, '.' ]
				ifFalse: [ ids add: each identifier asString ] ] ].
]
