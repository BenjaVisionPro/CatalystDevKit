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
BVCConnect >> catalystConnectPort [
	^ 20302
]

{ #category : #'as yet unclassified' }
BVCConnect >> initialize [

  super initialize.
  hosts := Dictionary new
]

{ #category : #'known hosts' }
BVCConnect >> localTestHost [

  ^ hosts at: #localTestHost ifAbsentPut: [
        BVCHost new
          hostName: 'localhost';
          yourself
      ]
]

{ #category : #'server - startup' }
BVCConnect >> startServerOnPort: aPort [
  "Start BVCConnect Server on aPort"

  ^( ZnServer startOn: aPort )
    delegate: BVCConnectServerDelegate new;
    yourself
]

{ #category : #'server - shutdown' }
BVCConnect >> stopServer: aServer [
  "Stop the default BVCConnect server"

  aServer stop
]
