Class {
	#name : 'CRScheduleContext',
	#superclass : 'Object',
	#instVars : [
		'key',
		'boundaryMillis'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRScheduleContext class >> key: aKey boundaryMillis: anInteger [
	^ self new
		key: aKey;
		boundaryMillis: anInteger;
		yourself
]

{ #category : 'accessing' }
CRScheduleContext >> boundaryMillis [
	^ boundaryMillis
]

{ #category : 'accessing' }
CRScheduleContext >> boundaryMillis: anObject [
	boundaryMillis := anObject
]

{ #category : 'accessing' }
CRScheduleContext >> key [
	^ key
]

{ #category : 'accessing' }
CRScheduleContext >> key: anObject [
	key := anObject
]
