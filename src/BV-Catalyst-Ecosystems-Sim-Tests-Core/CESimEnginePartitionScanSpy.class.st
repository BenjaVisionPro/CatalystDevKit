Class {
	#name : 'CESimEnginePartitionScanSpy',
	#superclass : 'CESimEngine',
	#instVars : [
		'partitionsWasCalled'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Tests-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Tests-Core'
}

{ #category : 'testing' }
CESimEnginePartitionScanSpy >> partitions [
	partitionsWasCalled := true.
	^ super partitions
]

{ #category : 'testing' }
CESimEnginePartitionScanSpy >> partitionsWasCalled [
	^ partitionsWasCalled ifNil: [ false ]
]
