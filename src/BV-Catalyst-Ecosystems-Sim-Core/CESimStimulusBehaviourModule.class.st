Class {
	#name : 'CESimStimulusBehaviourModule',
	#superclass : 'CESimEffectBehaviourModule',
	#category : 'BV-Catalyst-Ecosystems-Sim-Core',
	#package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'producing' }
CESimStimulusBehaviourModule >> applyStimulusCommand: aCommand intoUpdate: aCESimUpdate inContext: aCESimRunContext [
	| regionId |
	regionId := aCESimRunContext subject homeRegionId.

	"Non-targeted: affects whatever is perceived this tick."
	(self perceivedVisibleSnapshotsInContext: aCESimRunContext)
		do: [ :snap |
			| entityId |
			entityId := snap at: #entityId.

			aCESimUpdate
				addEntityOp: (CESimApplyStimulusToEntityOp
						withRegionId: regionId
						entityId: entityId
						stimulusType: aCommand stimulusType
						transform: aCommand transform
						intensity: aCommand intensity
						tickId: aCESimRunContext tickId) ]
]

{ #category : 'contributing' }
CESimStimulusBehaviourModule >> contributeIntoUpdate: aSimUpdate inContext: aSimContext [
	| commands |

	"Command contributions (may enqueue stimulus invocations for this tick)"
	commands := aSimContext runCache drainedCommands.
	commands do: [ :cmd |
		CESimCurrentOrigin value: cmd during: [
			cmd contributeStimulusIntoUpdate: aSimUpdate inContext: aSimContext
		]
	].

	"Capability invocations (e.g., targeted stimulus) - execute after commands"
	aSimContext runCache stimulusInvocations
		do: [ :invocation |
			CESimCurrentOrigin value: invocation during: [
				invocation contributeIntoUpdate: aSimUpdate inContext: aSimContext
			]
		].
]
