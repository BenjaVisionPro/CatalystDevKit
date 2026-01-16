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
  commands isEmpty ifTrue: [ ^ CESimUpdate new ].

  update := CESimUpdate new.
  commands do: [ :cmd |
    "Command contributes ops/events deterministically."
    cmd produceIntoUpdate: update inContext: aCESimRunContext.

    "Keep the existing acceptance event (still useful for tracing)."
    update addEvent: (self eventFromCommand: cmd stage: aStage context: aCESimRunContext).
  ].

  ^ update
]

{ #category : 'private' }
CESimConsumeCommandsStageRunner >> eventFromCommand: aCommand stage: aStage context: aCESimRunContext [
	"v0: represent commands/events as Dictionaries.
     This is an authoritative 'fact happened' event, derived from the command."

	^ Dictionary new
		at: #type put: #commandAccepted;
		at: #command put: aCommand;
		at: #tickId put: aCESimRunContext tickId;
		at: #stageId put: aStage stageId;
		yourself
]
