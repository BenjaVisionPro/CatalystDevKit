Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Architect-Core' }
Catalyst >> architect [
	^ plugins at: BVCArchitect ifAbsentPut: [ BVCArchitect new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Architect-Core' }
Catalyst class >> architect [
	^ self instance architect
]
