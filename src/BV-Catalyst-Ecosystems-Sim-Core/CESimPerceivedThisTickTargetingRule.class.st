Class {
	#name : 'CESimPerceivedThisTickTargetingRule',
	#superclass : 'CESimTargetingRule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimPerceivedThisTickTargetingRule >> rejectionReasonForTargetEntityId: anEntityId inContext: aContext [
	(aContext preEntitySnapshots
		anySatisfy: [ :snap | (snap at: #entityId) = anEntityId ]) ifTrue: [ ^ nil ].
	^ CESimDecisionOutcome notPerceived
]
