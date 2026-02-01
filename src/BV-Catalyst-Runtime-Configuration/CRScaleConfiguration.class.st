Class {
	#name : 'CRScaleConfiguration',
	#superclass : 'Object',
	#instVars : [
		'minCount',
		'maxCount',
		'minIdleCount',
		'maxIdleCount',
		'scaleUpBatchSize',
		'scaleDownBatchSize',
		'evaluationIntervalMillis',
		'cooldownMillis',
		'stabilizationWindowMillis'
	],
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'accessing' }
CRScaleConfiguration >> cooldownMillis [ ^ cooldownMillis
]

{ #category : 'accessing' }
CRScaleConfiguration >> cooldownMillis: anInteger [ cooldownMillis := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> evaluationIntervalMillis [ ^ evaluationIntervalMillis
]

{ #category : 'accessing' }
CRScaleConfiguration >> evaluationIntervalMillis: anInteger [ evaluationIntervalMillis := anInteger asInteger
]

{ #category : 'initialization' }
CRScaleConfiguration >> initialize [
	super initialize.
	minCount := 0.
	maxCount := 0.
	minIdleCount := 0.
	maxIdleCount := 0.
	scaleUpBatchSize := 1.
	scaleDownBatchSize := 1.
	evaluationIntervalMillis := 0.
	cooldownMillis := 0.
	stabilizationWindowMillis := nil
]

{ #category : 'accessing' }
CRScaleConfiguration >> maxCount [ ^ maxCount
]

{ #category : 'accessing' }
CRScaleConfiguration >> maxCount: anInteger [ maxCount := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> maxIdleCount [ ^ maxIdleCount
]

{ #category : 'accessing' }
CRScaleConfiguration >> maxIdleCount: anInteger [ maxIdleCount := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> minCount [ ^ minCount
]

{ #category : 'accessing' }
CRScaleConfiguration >> minCount: anInteger [ minCount := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> minIdleCount [ ^ minIdleCount
]

{ #category : 'accessing' }
CRScaleConfiguration >> minIdleCount: anInteger [ minIdleCount := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> scaleDownBatchSize [ ^ scaleDownBatchSize
]

{ #category : 'accessing' }
CRScaleConfiguration >> scaleDownBatchSize: anInteger [ scaleDownBatchSize := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> scaleUpBatchSize [ ^ scaleUpBatchSize
]

{ #category : 'accessing' }
CRScaleConfiguration >> scaleUpBatchSize: anInteger [ scaleUpBatchSize := anInteger asInteger
]

{ #category : 'accessing' }
CRScaleConfiguration >> stabilizationWindowMillis [ ^ stabilizationWindowMillis
]

{ #category : 'accessing' }
CRScaleConfiguration >> stabilizationWindowMillis: anIntegerOrNil [ stabilizationWindowMillis := anIntegerOrNil ifNil: [ nil ] ifNotNil: [ anIntegerOrNil asInteger ]
]

{ #category : 'validation' }
CRScaleConfiguration >> validateOn: aValidationResult forWorkerIdentifier: aWorkerIdentifier [
	(minCount isInteger and: [ minCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling minCount for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(maxCount isInteger and: [ maxCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling maxCount for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(maxCount >= minCount) ifFalse: [ aValidationResult addError: 'Scaling maxCount must be >= minCount for ', aWorkerIdentifier printString, '.' ].
	(scaleUpBatchSize isInteger and: [ scaleUpBatchSize > 0 ]) ifFalse: [ aValidationResult addError: 'Scaling scaleUpBatchSize for ', aWorkerIdentifier printString, ' must be > 0.' ].
	(scaleDownBatchSize isInteger and: [ scaleDownBatchSize > 0 ]) ifFalse: [ aValidationResult addError: 'Scaling scaleDownBatchSize for ', aWorkerIdentifier printString, ' must be > 0.' ].
	(evaluationIntervalMillis isInteger and: [ evaluationIntervalMillis >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling evaluationIntervalMillis for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(cooldownMillis isInteger and: [ cooldownMillis >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling cooldownMillis for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(minIdleCount isInteger and: [ minIdleCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling minIdleCount for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(maxIdleCount isInteger and: [ maxIdleCount >= 0 ]) ifFalse: [ aValidationResult addError: 'Scaling maxIdleCount for ', aWorkerIdentifier printString, ' must be >= 0.' ].
	(maxIdleCount >= minIdleCount) ifFalse: [ aValidationResult addError: 'Scaling maxIdleCount must be >= minIdleCount for ', aWorkerIdentifier printString, '.' ].
]
