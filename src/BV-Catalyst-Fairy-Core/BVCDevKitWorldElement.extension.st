Extension { #name : 'BVCDevKitWorldElement' }

{ #category : '*BV-Catalyst-Fairy-Core' }
BVCDevKitWorldElement >> onGtPhlowObjectToSpawn: aSpawnEvent [
	"The world spawn path does not derive a window title from the chat tool."
	(aSpawnEvent object isKindOf: BVCFairyChat)
		ifFalse: [ ^ super onGtPhlowObjectToSpawn: aSpawnEvent ].
	aSpawnEvent consumed: true.
	BlSpace new
		withCommonSettings;
		title: 'Barry';
		inPager: aSpawnEvent tool;
		showFrom: self
]
