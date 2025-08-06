Class {
	#name : #BVCConnectTests,
	#superclass : #TestCase,
	#instVars : [
		'server',
		'client'
	],
	#category : #'BV-Catalyst-Tests-Connect-Core'
}

{ #category : #messages }
BVCConnectTests >> helloMessage [
  "Answer a hello message"

  ^ ( NeoJSONObject new
        atPath: #( 'protocol' 'type' ) put: 'bv_connect_p';
        atPath: #( 'protocol' 'version' ) put: 1.0;
        atPath: #( 'payload' 'action' ) put: 'hello';
        yourself ) printString
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> newWebSocketToTestServer [

  ^ ZnWebSocket to: 'ws://localhost:' , self testPort asString , '/connect'
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> setUp [

  super setUp.
  server := BVCConnectServer new startOnPort: self testPort
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> tearDown [

  super tearDown.
  server stop.
  server := nil
]

{ #category : #'as yet unclassified' }
BVCConnectTests >> testConnectServer [

  client := self newWebSocketToTestServer.
  client sendMessage: self helloMessage.
  server delegate 
  
]

{ #category : #defaults }
BVCConnectTests >> testPort [

  ^ 1701
]
