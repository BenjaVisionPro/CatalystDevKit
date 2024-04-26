Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Store-Core' }
Catalyst >> store [
	^ plugins at: BVCStore ifAbsentPut: [ BVCStore new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Store-Core' }
Catalyst class >> store [
	^ self instance store
]
