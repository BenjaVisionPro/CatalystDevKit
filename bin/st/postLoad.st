(BlParallelUniverse all detect: [ :u | u hostClass == BlMorphicWindowHost ]) 
	ifNotNil: [ :pu |
		pu spaces do: #close.
		pu
			tryToRunDeferredActions;
			stopUniverse.
	].

BVCDevKit initializeKnowledgeBase.
BVCDevKitWorld openDefault.
SmalltalkImage current saveAs: 'BVCDevKit'.