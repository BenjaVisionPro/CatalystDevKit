Class {
	#name : 'CESimConsumeCommandsStageRunner',
	#superclass : 'CESimUpdateStageRunner',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'running' }
CESimConsumeCommandsStageRunner >> buildUpdateForStage: aStage inContext: aCESimRunContext [
  | bubble commands update |
	bubble := aCESimRunContext subject.
	commands := bubble drainCommands.

	"Publish drained commands for later stages (ResolveIntent)."
	aCESimRunContext stepCacheAt: #drainedCommands put: commands.

	commands isEmpty ifTrue: [ ^ CESimUpdate new ].

	update := CESimUpdate new.
	commands do: [ :cmd |
		update addEvent: (self
			eventFromCommand: cmd
			stage: aStage
			context: aCESimRunContext)
	].
	^ update
]

{ #category : 'private' }
CESimConsumeCommandsStageRunner >> eventFromCommand: aCommand stage: aStage context: aCESimRunContext [
	^ Dictionary new
		at: #type put: #commandAccepted;
		at: #command put: aCommand;
		at: #tickId put: aCESimRunContext tickId;
		at: #stageId put: aStage stageId;
		yourself
]
