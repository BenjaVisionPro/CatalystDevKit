Class {
	#name : #BVCConnectHelloMessage,
	#superclass : #BVCConnectMessage,
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #'as yet unclassified' }
BVCConnectHelloMessage >> messageTypes [

  ^ super messageTypes
      add: 'hello';
      yourself
]
