Extension { #name : 'GtLFunctionToolCall' }

{ #category : '*BV-Catalyst-Fairy-Core' }
GtLFunctionToolCall >> catalystAgentExecution [
	^ runtimeValues at: #catalystAgentExecution ifAbsent: [ nil ]
]
