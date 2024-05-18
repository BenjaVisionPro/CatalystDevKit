Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Architect-Core' }
Catalyst >> architect [
	^ plugins at: BVCArchitect ifAbsentPut: [ BVCArchitect new ]
		
]

{ #category : #'*BV-Catalyst-Architect-Core' }
Catalyst class >> architect [
	^ self instance architect
]
