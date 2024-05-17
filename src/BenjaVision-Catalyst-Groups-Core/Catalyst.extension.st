Extension { #name : #Catalyst }

{ #category : #'*BV-Catalyst-Groups-Core' }
Catalyst class >> groups [
	^ self instance groups
]

{ #category : #'*BV-Catalyst-Groups-Core' }
Catalyst >> groups [
	^ plugins at: BVCGroups ifAbsentPut: [ BVCGroups new ]
		
]
