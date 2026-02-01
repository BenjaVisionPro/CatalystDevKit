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
CRWorkSchedulerConfiguration >> validateOn: result forWorkerIdentifier: workerIdentifier [
	| ids workerLabel |
	workerLabel := workerIdentifier
			ifNil: [ '<nil>' ]
			ifNotNil: [ workerIdentifier printString ].

	schedules isNil
		ifTrue: [ ^ result
				addError: 'Worker ' , workerLabel , ' scheduler schedules is required.' ].

	schedules isCollection
		ifFalse: [ ^ result
				addError: 'Worker ' , workerLabel , ' scheduler schedules must be a collection; got '
						, schedules printString , ' (' , schedules class name , ').' ].

	ids := Set new.
	schedules
		do: [ :each | 
			each validateOn: result forWorkerIdentifier: workerIdentifier.

			each identifier isNil
				ifFalse: [ (ids includes: each identifier)
						ifTrue: [ result
								addError: 'Worker ' , workerLabel , ' has duplicate schedule identifier '
										, each identifier printString , '.' ]
						ifFalse: [ ids add: each identifier ] ] ]
]
