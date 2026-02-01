Class {
	#name : 'CRWorkerSnapshot',
	#superclass : 'Object',
	#instVars : [
		'workerIdentifier',
		'instanceOrdinal',
		'hostIdentifier',
		'status'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRWorkerSnapshot >> hostIdentifier [ ^ hostIdentifier ]
{ #category : 'accessing' }
CRWorkerSnapshot >> hostIdentifier: aString [ hostIdentifier := aString asString ]

{ #category : 'initialization' }
CRWorkerSnapshot >> initialize [
	super initialize.
	workerIdentifier := ''.
	instanceOrdinal := 0.
	hostIdentifier := ''.
	status := nil
]

{ #category : 'accessing' }
CRWorkerSnapshot >> instanceOrdinal [ ^ instanceOrdinal ]
{ #category : 'accessing' }
CRWorkerSnapshot >> instanceOrdinal: anInteger [ instanceOrdinal := anInteger asInteger ]

{ #category : 'accessing' }
CRWorkerSnapshot >> status [ ^ status ]
{ #category : 'accessing' }
CRWorkerSnapshot >> status: anObject [ status := anObject ]

{ #category : 'accessing' }
CRWorkerSnapshot >> workerIdentifier [ ^ workerIdentifier ]
{ #category : 'accessing' }
CRWorkerSnapshot >> workerIdentifier: aString [ workerIdentifier := aString asString ]
