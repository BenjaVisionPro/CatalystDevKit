Class {
	#name : #BVCServerDelegate,
	#superclass : #Object,
	#instVars : [
		'handler'
	],
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #protocol }
BVCServerDelegate >> continuation [
	"Return a block that defines what happens after a successful connection upgrade.
	We will receive a ready-to-use instanciated WebSocket.
	We delegate processing to our handler."

	^ [ :webSocket | handler value: webSocket ]
]

{ #category : #defaults }
BVCServerDelegate >> delegateUri [
	^ self subclassResponsibility
]

{ #category : #'request handling' }
BVCServerDelegate >> handleRequest: request [
  "Server delegate entry point"

  ( self isHandlerForRequest: request ) ifFalse: [ ^ ZnResponse notFound: request uri ].
  ^ ( self isValidWebSocketRequest: request )
      ifTrue: [ self webSocketResponseForRequest: request ]
      ifFalse: [ ZnResponse badRequest: request ]
]

{ #category : #initialization }
BVCServerDelegate >> initialize [

  super initialize.
  handler := self messageHandlerClass new
]

{ #category : #'request handling' }
BVCServerDelegate >> isHandlerForRequest: request [

  ^ ( self delegateUri findTokens: '/' ) = request uri pathSegments
]

{ #category : #protocol }
BVCServerDelegate >> isValidWebSocketRequest: request [
	"Return true when request can be considered a valid WebSocket setup request"
	
	^ request method = #GET
			and: [ (request headers at: 'Upgrade' ifAbsent: [ ^ false ]) asLowercase = 'websocket' 
				and: [ (ZnWebSocketUtils containsConnectionUpgrade: request headers) 
					and: [ (request headers at: 'Sec-WebSocket-Version' ifAbsent: [ ^ false ]) = '13'
						and: [ request headers includesKey: 'Sec-WebSocket-Key' ] ] ] ]
]

{ #category : #'request handling' }
BVCServerDelegate >> messageHandlerClass [
	^ self subclassResponsibility
]

{ #category : #'request handling' }
BVCServerDelegate >> protocolIdentifier [
	^ self subclassResponsibility
]

{ #category : #'request handling' }
BVCServerDelegate >> responseHeadersForKey: key [
	"Return the headers for a WebSocket setup response, given key"
	
	^ ZnHeaders defaultResponseHeaders
			at: 'Upgrade' put: 'websocket';
			at: 'Connection' put: 'Upgrade';
			at: 'Sec-WebSocket-Accept' put: key;
			at: 'Sec-WebSocket-Protocol' put: self protocolIdentifier;
			yourself
]

{ #category : #'request handling' }
BVCServerDelegate >> value: request [
	"I implement the generic #value: message as equivalent to #handleRequest:"
	
	^ self handleRequest: request
]

{ #category : #'request handling' }
BVCServerDelegate >> webSocketResponseForRequest: request [
	"Given a valid WebSocket setup request, return the matching server response"
	
	| acceptKey |
	acceptKey := ZnWebSocketUtils handshake: (request headers at: 'Sec-WebSocket-Key').
	^ ZnWebSocketResponse new
		statusLine: (ZnStatusLine code: 101);
		headers: (self responseHeadersForKey: acceptKey);
		continuation: self continuation;
		yourself
]
