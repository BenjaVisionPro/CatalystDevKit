"
I am the Entry Point for all Catalyst Connect features.
"
Class {
	#name : #BVCConnect,
	#superclass : #BVCPlugin,
	#instVars : [
		'hosts'
	],
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #defaults }
BVCConnect >> defaultPort [
	^ 20302
]

{ #category : #defaults }
BVCConnect >> defaultServer [
	"Answer the default Zinc server"
	^ ZnServer default
]

{ #category : #'server - startup' }
BVCConnect >> startServer [
	"Starts the default BVCConnectServer on the default port"
	self startServerOnPort: self defaultPort
	
]

{ #category : #'server - startup' }
BVCConnect >> startServerOnPort: aPort [
  "Start BVCConnect Server on aPort"

  ( ZnServer startDefaultOn: aPort ) delegate: BVCConnectServerDelegate new
]

{ #category : #'server - shutdown' }
BVCConnect >> stopServer [
	"Stop the default BVCConnect server"
	ZnServer default stop
]
