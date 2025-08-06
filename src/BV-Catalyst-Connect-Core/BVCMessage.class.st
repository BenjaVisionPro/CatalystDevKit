Class {
	#name : #BVCMessage,
	#superclass : #Object,
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #'instance creation' }
BVCMessage class >> fromJsonBytes: bytes [
  "Marshal bytes into the message"

  | json type |
  json := ( NeoJSONReader on: ( ReadStream on: bytes ) ) next.
  type := self messageClassForType: ( json atPath: #( 'message' 'type' ) ).
  ^ type fromJson: json
]

{ #category : #'instance creation' }
BVCMessage class >> messageClassForType: type [

  ^ BVCMessage allSubclasses
      detect: [ :messageClass | messageClass types includes: type ]
      ifNone: [ self error: 'No Message class handles type "' , type , '".' ]
]

{ #category : #marshalling }
BVCMessage >> fromJson: json [
  "Marshal json into the message"

  self magritteDescription do: [ :desc |  ]
]

{ #category : #'as yet unclassified' }
BVCMessage >> messageTypes [

  ^ #(  )
]
