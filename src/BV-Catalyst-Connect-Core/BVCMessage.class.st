Class {
	#name : #BVCMessage,
	#superclass : #Object,
	#category : #'BV-Catalyst-Connect-Core'
}

{ #category : #'instance creation' }
BVCMessage class >> fromBytes: bytes [

  ^ self new fromBytes: bytes
]

{ #category : #marshalling }
BVCMessage >> fromBytes: bytes [

  | json |
  "Marshal bytes into a message"
  json := ( NeoJSONReader on: ( ReadStream on: bytes ) ) next
]
