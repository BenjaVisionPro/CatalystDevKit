Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Users-Core' }
Catalyst >> users [
	^ plugins at: BVCUsers ifAbsentPut: [ BVCUsers new ]
		
]

{ #category : #'*BV-Catalyst-Users-Core' }
Catalyst class >> users [
	^ self instance users
]
