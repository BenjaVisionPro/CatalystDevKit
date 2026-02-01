Class {
	#name : 'CRHostSnapshot',
	#superclass : 'Object',
	#instVars : [
		'hostIdentifier',
		'runningProcessCount',
		'maxProcesses'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRHostSnapshot >> hostIdentifier [ ^ hostIdentifier
]

{ #category : 'accessing' }
CRHostSnapshot >> hostIdentifier: aSymbol [
	hostIdentifier := aSymbol
]

{ #category : 'initialization' }
CRHostSnapshot >> initialize [
	super initialize.
	hostIdentifier := ''.
	runningProcessCount := 0.
	maxProcesses := 0
]

{ #category : 'accessing' }
CRHostSnapshot >> maxProcesses [ ^ maxProcesses
]

{ #category : 'accessing' }
CRHostSnapshot >> maxProcesses: anInteger [ maxProcesses := anInteger asInteger
]

{ #category : 'accessing' }
CRHostSnapshot >> runningProcessCount [ ^ runningProcessCount
]

{ #category : 'accessing' }
CRHostSnapshot >> runningProcessCount: anInteger [ runningProcessCount := anInteger asInteger
]
