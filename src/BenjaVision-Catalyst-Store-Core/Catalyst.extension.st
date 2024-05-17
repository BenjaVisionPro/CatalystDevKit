Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Store-Core' }
Catalyst >> store [
	^ plugins at: BVCStore ifAbsentPut: [ BVCStore new ]
		
]

{ #category : #'*BV-Catalyst-Store-Core' }
Catalyst class >> store [
	^ self instance store
]
