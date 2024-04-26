Extension { #name : #Catalyst }

{ #category : #'*BenjaVision-Catalyst-Groups-Core' }
Catalyst class >> groups [
	^ self instance groups
]

{ #category : #'*BenjaVision-Catalyst-Groups-Core' }
Catalyst >> groups [
	^ plugins at: BVCGroups ifAbsentPut: [ BVCGroups new ]
		
]
