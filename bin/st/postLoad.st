[
	BVCDevKit initializeKnowledgeBase.
	space := BVCDevKitWorld openDefault. 
	5 seconds wait
] on: Error do: [ :e | 
	Smalltalk logError: e messageText inContext: e signalerContext. 
	Smalltalk exitFailure 
]. 
Smalltalk garbageCollect; garbageCollect; garbageCollect.
5 seconds wait.
"space universe snapshot: true andQuit: true."