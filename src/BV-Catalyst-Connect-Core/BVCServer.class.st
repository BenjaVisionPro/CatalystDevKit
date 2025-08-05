Class {
	#name : #BVCServer,
	#superclass : #Object,
	#instVars : [
		'server'
	],
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #defaults }
BVCServer >> delegateClass [
  "The delegate for handling requests from this server"

  ^ self subclassResponsibility
]

{ #category : #defaults }
BVCServer >> serverPort [
  "The listener port for this server"

  ^ self subclassResponsibility
]

{ #category : #'server-startup' }
BVCServer >> start [
	"Start the server"
	self startOnPort: self serverPort
]

{ #category : #'server-startup' }
BVCServer >> startOnPort: aPortNumber [
  "Start the server listening on aPortNumber"

  server
    ifNil: [
        server := ( ZnServer startOn: aPortNumber )
                    delegate: self delegateClass new;
                    yourself
      ]
    ifNotNil: [ self error: 'Server is already running' ]
]

{ #category : #'server-startup' }
BVCServer >> stop [
  "Stop the server"

  server ifNil: [ self error: 'There is no server to stop' ] ifNotNil: [
      server stop.
      server := nil
    ]
]
