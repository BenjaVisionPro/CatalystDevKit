Class {
	#name : #BVCConnectServerDelegate,
	#superclass : #BVCServerDelegate,
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #'as yet unclassified' }
BVCConnectServerDelegate >> delegateUri [
	"URI path to this entry point"
	^'connect'
]

{ #category : #'as yet unclassified' }
BVCConnectServerDelegate >> messageHandlerClass [
	^ BVCConnectMessageHandler
]

{ #category : #'as yet unclassified' }
BVCConnectServerDelegate >> protocolIdentifier [
	^ 'bvc_connect_p'
]
