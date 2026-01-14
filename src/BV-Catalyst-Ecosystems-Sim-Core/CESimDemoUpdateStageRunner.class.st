Class {
	#name : 'CESimDemoUpdateStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'as yet unclassified' }
CESimDemoUpdateStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
	| update event |
	update := CESimUpdate new.

	event := Dictionary new
			at: #type put: #demoEvent;
			at: #tickId put: aCESimRunContext tickId;
			at: #stageId put: aStage stageId;
			yourself.

	update addEvent: event.
	^ update
]
