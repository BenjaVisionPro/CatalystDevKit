Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Connect-Core' }
Catalyst >> connect [
	^ plugins at: BVCConnect ifAbsentPut: [ BVCConnect new ]
		
]

{ #category : #'*BV-Catalyst-Connect-Core' }
Catalyst class >> connect [
	^ self instance connect
]
