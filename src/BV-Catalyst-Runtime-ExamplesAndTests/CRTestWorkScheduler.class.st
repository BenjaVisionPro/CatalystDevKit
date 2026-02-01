Class {
	#name : 'CRTestWorkScheduler',
	#superclass : 'CRWorkScheduler',
	#instVars : [
		'nowMillis'
	],
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'time' }
CRTestWorkScheduler >> currentMillis [
	^ nowMillis
]

{ #category : 'time' }
CRTestWorkScheduler >> nowMillis: anInteger [
	nowMillis := anInteger
]
