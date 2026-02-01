Class {
	#name : 'CRRuntimeConfigurationCodecTests',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRRuntimeConfigurationCodecTests >> test_roundTrip_devExample_isValid [
	| cfg ston loaded |
	cfg := CRRuntimeConfigurationExamples devLocal.

	ston := CRRuntimeConfigurationCodec toStringPretty: cfg.
	loaded := CRRuntimeConfigurationCodec fromString: ston.

	self assert: (loaded isKindOf: CRRuntimeConfiguration).
	self assert: loaded validate isValid.
]

{ #category : 'tests' }
CRRuntimeConfigurationCodecTests >> test_roundTrip_testingExample_isValid [
	| cfg ston loaded |
	cfg := CRRuntimeConfigurationExamples testingLocal.

	ston := CRRuntimeConfigurationCodec toStringPretty: cfg.
	loaded := CRRuntimeConfigurationCodec fromString: ston.

	self assert: loaded validate isValid.
]

{ #category : 'tests' }
CRRuntimeConfigurationCodecTests >> test_stonText_containsSymbolIdentifiers [
	| cfg ston |
	cfg := CRRuntimeConfigurationExamples devLocal.
	ston := CRRuntimeConfigurationCodec toStringPretty: cfg.

	self assert: (ston includesSubstring: '#gateway').
	self assert: (ston includesSubstring: '#local').
	self assert: (ston includesSubstring: '#heartbeat').
]
