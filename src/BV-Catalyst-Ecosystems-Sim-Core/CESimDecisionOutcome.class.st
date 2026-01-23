Class {
	#name : 'CESimDecisionOutcome',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'reasons' }
CESimDecisionOutcome class >> all [
	^ {self notPresent.
		self notPerceived.
		self noPolicy} asSet
]

{ #category : 'reasons' }
CESimDecisionOutcome class >> noPolicy [
	"No configured policy/rules exist for the requested profile."

	^ #noPolicy
]

{ #category : 'reasons' }
CESimDecisionOutcome class >> notPerceived [
	"Reference exists but is not in this tick's perceived/observable set."

	^ #notPerceived
]

{ #category : 'reasons' }
CESimDecisionOutcome class >> notPresent [
	"Required reference (owner/target/etc.) is missing in this context."

	^ #notPresent
]
