Class {
	#name : #BVCConnectMessageHandler,
	#superclass : #Object,
	#instVars : [
		'sockets',
		'lock'
	],
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #'as yet unclassified' }
BVCConnectMessageHandler >> initialize [
	sockets := OrderedCollection new.
	lock := Mutex new
]

{ #category : #'as yet unclassified' }
BVCConnectMessageHandler >> register: clientWebSocket [
	lock critical: [
		sockets add: clientWebSocket ]
]

{ #category : #'as yet unclassified' }
BVCConnectMessageHandler >> triageMessage: message [ 
	"I triage incoming messages and delegate to the appropriate handler"
	
]

{ #category : #'as yet unclassified' }
BVCConnectMessageHandler >> unregister: clientWebSocket [
	lock critical: [
		sockets remove: clientWebSocket ifAbsent: [ ] ]
]

{ #category : #'as yet unclassified' }
BVCConnectMessageHandler >> value: webSocket [
	"I keep a list of active clients (don't know why, but I do it anyway) and send messages to triage"
	[
		self register: webSocket.
		webSocket runWith: [ :message |
			webSocket logGeneric: 'Received message: ', message printString.
			self triageMessage: message.
			] ] 
		on: NetworkError 
		do: [
			webSocket logGeneric: 'Network error, cleaning up'.
			self unregister: webSocket ]
]
