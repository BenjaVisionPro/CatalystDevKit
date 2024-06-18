5 second wait.
GtWorld allInstances first removeShutdownListener.
BlParallelUniverse all do: [ :universe | 
	universe spaces do: #close.
	universe tryToRunDeferredActions.
	1 second wait.
	universe hostClass == BIMorphicWindowHost ifTrue: [ universe stopUniverse ].
].
20 second wait.

BVCDevKit initializeKnowledgeBase.
BVCDevKitWorld openDefault.
30 second wait.
SmalltalkImage current saveAs: 'BVCDevKit'.
30 second wait.