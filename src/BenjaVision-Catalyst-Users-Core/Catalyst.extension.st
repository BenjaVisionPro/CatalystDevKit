Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Users-Core' }
Catalyst >> users [
	^ plugins at: BVCUsers ifAbsentPut: [ BVCUsers new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Users-Core' }
Catalyst class >> users [
	^ self instance users
]
