Class {
	#name : 'CESimUpdateApplier',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimUpdateApplier >> applyUpdate: aCESimUpdate toAggregate: anAggregate inContext: aCESimRunContext [
	"v0: apply only events as facts for inspection."

	aCESimUpdate events do: [ :eachEvent | anAggregate appendEvent: eachEvent ]
]

{ #category : 'applying' }
CESimUpdateApplier >> applyUpdatesInContext: aCESimRunContext [
	| aggregate |
	aggregate := aCESimRunContext subject.

	aCESimRunContext updates
		do: [ :eachUpdate | 
			self
				applyUpdate: eachUpdate
				toAggregate: aggregate
				inContext: aCESimRunContext ].

	aCESimRunContext clearUpdates
]
