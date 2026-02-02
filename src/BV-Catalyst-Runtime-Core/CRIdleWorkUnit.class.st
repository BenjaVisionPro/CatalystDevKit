Class {
	#name : 'CRIdleWorkUnit',
	#superclass : 'CRWorkUnit',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'running' }
CRIdleWorkUnit >> executeWorkUnitInContext: aCRWorkUnitExecutionContext [
	"Idle is currently a no-op.
	Future: a clean hook for idle stats/telemetry if we want it."

	"intentionally empty"

	
]
