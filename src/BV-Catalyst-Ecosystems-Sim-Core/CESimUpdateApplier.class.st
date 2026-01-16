Class {
	#name : 'CESimUpdateApplier',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'applying' }
CESimUpdateApplier >> applyUpdate: aCESimUpdate toAggregate: anAggregate inContext: aCESimRunContext [
	| ops |
	ops := (aCESimUpdate entityOps asSortedCollection: [ :a :b | a before: b ]) asOrderedCollection.
	ops do: [ :eachOp | eachOp applyInContext: aCESimRunContext ].

	"Keep events as inspection facts on the subject aggregate (v0 behaviour)."
	aCESimUpdate events do: [ :eachEvent | anAggregate appendEvent: eachEvent ].

	"patches lane intentionally left for later"
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
