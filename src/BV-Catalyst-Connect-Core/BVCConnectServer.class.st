Class {
	#name : #BVCConnectServer,
	#superclass : #BVCServer,
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #defaults }
BVCConnectServer >> delegateClass [
  "The delegate for handling requests from this server"

  ^ BVCConnectServerDelegate
]

{ #category : #defaults }
BVCConnectServer >> serverPort [
  "Default listener port for BVC Connect"

  ^ 20302
]
