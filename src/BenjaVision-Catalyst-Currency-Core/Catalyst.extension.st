Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Currency-Core' }
Catalyst >> currency [
	^ plugins at: BVCCurrency ifAbsentPut: [ BVCCurrency new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Currency-Core' }
Catalyst class >> currency [
	^ self instance currency
]
