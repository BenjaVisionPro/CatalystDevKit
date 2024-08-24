"
I connect to a running UE Editor client to allow remote control
"
Class {
	#name : #BVCUnrealEngineRemoteControlApi,
	#superclass : #BVCApplicationComponent,
	#instVars : [
		'webSocket'
	],
	#category : #'BV-Catalyst-Core'
}

{ #category : #'as yet unclassified' }
BVCUnrealEngineRemoteControlApi >> connect [
	"Connect to Unreal Editor running on the same machine"
	webSocket := ZnWebSocket to: 'ws://127.0.0.1:30020'
]
