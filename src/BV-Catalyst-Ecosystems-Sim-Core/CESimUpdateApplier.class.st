Class {
	#name : 'CESimUpdateApplier',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimUpdateApplier >> applyUpdate: aCESimUpdate toAggregate: anAggregate inContext: aCESimRunContext [
	"Apply update facts (events) + authoritative changes (entity ops)."

	"Facts for inspection/debugging."
	aCESimUpdate events do: [ :eachEvent | anAggregate appendEvent: eachEvent ].

	"Authoritative changes (deterministic ordering)."
	(aCESimUpdate entityOps asSortedCollection: [ :a :b | a before: b ])
		do: [ :eachOp | eachOp applyInContext: aCESimRunContext ].

	"v0 patches are now legacy; leave them unused/empty until removed."
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
