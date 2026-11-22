"
Produces an ACF-ready manifest from portable gear definitions and reference cases.
"
Class {
	#name : 'BVCACFGearExporter',
	#superclass : 'Object',
	#category : 'BV-Catalyst-UE-Core',
	#package : 'BV-Catalyst-UE-Core'
}

{ #category : 'exporting' }
BVCACFGearExporter >> exportItems: items family: family encounter: encounter reference: cases to: file [
	| document |
	document := {'schema' -> 'catalyst-acf-gear-v1'.
			'items' -> (items collect: [ :item | self itemRecordFor: item ]).
			'family'
				-> {'id' -> family id asString.
						'manufacturer' -> family manufacturer.
						'tiers' -> (family tiers collect: [ :tier | self tierRecordFor: tier ])}
						asOrderedDictionary.
			'encounter' -> encounter.
			'reference' -> cases} asOrderedDictionary.
	file asFileReference parent ensureCreateDirectory.
	file asFileReference
		writeStreamDo: [ :stream | 
			stream
				nextPutAll: (STONJSON toStringPretty: document);
				lf ].
	^ document
]

{ #category : 'exporting' }
BVCACFGearExporter >> itemRecordFor: item [
	^ {'id' -> item id asString.
		'name' -> item displayName.
		'icon' -> item icon.
		'type' -> item gearType asString.
		'slot' -> item slot asString.
		'family' -> item familyId asString.
		'modifiers'
			-> (item modifiers collect: [ :modifier | self modifierRecordFor: modifier ])}
		asOrderedDictionary
]

{ #category : 'exporting' }
BVCACFGearExporter >> modifierRecordFor: modifier [
	^ {'stat' -> modifier stat asString.
		'operation' -> modifier operation asString.
		'magnitude' -> modifier magnitude asFloat.
		'target'
			-> (modifier targetClass ifNil: [ '' ] ifNotNil: [ :target | target asString ]).
		'duration' -> modifier duration asString} asOrderedDictionary
]

{ #category : 'exporting' }
BVCACFGearExporter >> tierRecordFor: tier [
	^ {'pieces' -> tier pieceCount.
		'limit' -> tier limit.
		'trigger'
			-> (tier trigger ifNil: [ '' ] ifNotNil: [ :event | event asString ]).
		'consumeOn'
			-> (tier consumeEvent ifNil: [ '' ] ifNotNil: [ :event | event asString ]).
		'modifiers'
			-> (tier modifiers collect: [ :modifier | self modifierRecordFor: modifier ])}
		asOrderedDictionary
]
