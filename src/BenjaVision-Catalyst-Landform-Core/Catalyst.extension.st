Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Landform-Core' }
Catalyst >> landform [
	^ plugins at: BVCLandform ifAbsentPut: [ BVCLandform new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Landform-Core' }
Catalyst class >> landform [
	^ self instance landform
]
