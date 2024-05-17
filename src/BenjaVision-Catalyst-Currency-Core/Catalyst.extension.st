Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Currency-Core' }
Catalyst >> currency [
	^ plugins at: BVCCurrency ifAbsentPut: [ BVCCurrency new ]
		
]

{ #category : #'*BV-Catalyst-Currency-Core' }
Catalyst class >> currency [
	^ self instance currency
]
