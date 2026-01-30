Class {
	#name : 'CRStopMode',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'modes' }
CRStopMode class >> all [
	^ {self none.
		self graceful.
		self immediate}
]

{ #category : 'modes' }
CRStopMode class >> graceful [
	^ #graceful
]

{ #category : 'modes' }
CRStopMode class >> immediate [
	^ #immediate
]

{ #category : 'modes' }
CRStopMode class >> none [
	^ #none
]
