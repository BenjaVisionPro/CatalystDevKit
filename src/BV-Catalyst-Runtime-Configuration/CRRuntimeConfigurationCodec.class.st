Class {
	#name : 'CRRuntimeConfigurationCodec',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'reading/writing' }
CRRuntimeConfigurationCodec class >> readFrom: aStream [
	"We haven't verified the chosen serializer in this codebase yet."
	self error: 'Configuration codec not implemented yet (serializer not chosen/verified).'
]

{ #category : 'reading/writing' }
CRRuntimeConfigurationCodec class >> write: aCRRuntimeConfiguration on: aStream [
	"We haven't verified the chosen serializer in this codebase yet."
	self error: 'Configuration codec not implemented yet (serializer not chosen/verified).'
]
