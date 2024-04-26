Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Connect-Core' }
Catalyst >> connect [
	^ plugins at: BVCConnect ifAbsentPut: [ BVCConnect new ]
		
]

{ #category : #'*BenjaVision-Catalyst-Connect-Core' }
Catalyst class >> connect [
	^ self instance connect
]
