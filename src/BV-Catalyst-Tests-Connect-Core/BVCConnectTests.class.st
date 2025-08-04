Class {
	#name : #BVCConnectTests,
	#superclass : #TestCase,
	#instVars : [
		'server'
	],
	#category : #'BV-Catalyst-Tests-Connect-Core'
}

{ #category : #'as yet unclassified' }
BVCConnectTests >> setUp [
	super setUp.
	Catalyst connect startServer.
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> tearDown [
	super tearDown.
	Catalyst connect stopServer.
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> testConnectServer [
	| webSocket |
	webSocket := ZnWebSocket to: 'ws://localhost:20302/connect'.
]
