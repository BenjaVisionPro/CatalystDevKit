Class {
	#name : 'CRRuntimeConfigurationCodec',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Configuration',
	#package : 'BV-Catalyst-Runtime-Configuration'
}

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> fromStream: aReadStream [
	^ STON fromStream: aReadStream
]

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> fromString: aString [
	^ STON fromString: aString
]

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> toString: aCRRuntimeConfiguration [
	^ STON toString: aCRRuntimeConfiguration
]

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> toStringPretty: aCRRuntimeConfiguration [
	^ STON toStringPretty: aCRRuntimeConfiguration
]

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> write: aCRRuntimeConfiguration onStream: aWriteStream [
	STON put: aCRRuntimeConfiguration onStream: aWriteStream
]

{ #category : 'reading / writing' }
CRRuntimeConfigurationCodec class >> writePretty: aCRRuntimeConfiguration onStream: aWriteStream [
	STON put: aCRRuntimeConfiguration onStreamPretty: aWriteStream
]
