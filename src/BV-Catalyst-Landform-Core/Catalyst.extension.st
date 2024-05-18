Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Landform-Core' }
Catalyst >> landform [
	^ plugins at: BVCLandform ifAbsentPut: [ BVCLandform new ]
		
]

{ #category : #'*BV-Catalyst-Landform-Core' }
Catalyst class >> landform [
	^ self instance landform
]
