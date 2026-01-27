Class {
	#name : 'CESimInvocationEnvelope',
	#superclass : 'Object',
	#instVars : [
		'invocationId',
		'bubbleId',
		'gatewayId',
		'playerIntentTickId',
		'invocation'
	],
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimInvocationEnvelope class >> invocationId: anInvocationId bubbleId: aBubbleId gatewayId: aGatewayId playerIntentTickId: aTickId invocation: aCESimInvocation [
	^ self new
		invocationId: anInvocationId;
		bubbleId: aBubbleId;
		gatewayId: aGatewayId;
		playerIntentTickId: aTickId;
		invocation: aCESimInvocation;
		yourself
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> envelopeId [
	"1:1 mapping. Envelope id is the wrapped invocation id."
	^ invocationId
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> invocationId [
	^ invocationId
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> invocationId: anObject [
	invocationId := anObject
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> bubbleId [
	^ bubbleId
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> bubbleId: anObject [
	bubbleId := anObject
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> gatewayId [
	^ gatewayId
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> gatewayId: anObject [
	gatewayId := anObject
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> playerIntentTickId [
	^ playerIntentTickId
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> playerIntentTickId: anObject [
	playerIntentTickId := anObject
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> invocation [
	^ invocation
]

{ #category : 'accessing' }
CESimInvocationEnvelope >> invocation: anObject [
	invocation := anObject
]
