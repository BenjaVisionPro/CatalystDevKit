Class {
	#name : 'CECreatureEntity',
	#superclass : 'CESimAgentEntity',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CECreatureEntity class >> id: aCEEntityId definitionKey: aDefinitionKey transform: aTransformDict state: aStateDict [
	^ (super id: aCEEntityId definitionKey: aDefinitionKey)
		transform: aTransformDict;
		state: aStateDict;
		yourself
]
