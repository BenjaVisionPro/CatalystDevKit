5 second wait.
GtWorld allInstances first removeShutdownListener.
BlParallelUniverse all do: [ :universe | 
	universe spaces ifNotEmpty: [ 
		universe spaces do: [ :space | universe closeSpaceSynchronously: space].
	].
	universe hostClass == BIMorphicWindowHost ifTrue: [ 
		universe stopUniverse
	].
].
BVCDevKit initializeKnowledgeBase.
BVCDevKitWorld openDefault.
2 second wait.
SmalltalkImage current saveAs: 'BVCDevKit'.
