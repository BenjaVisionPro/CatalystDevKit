Class {
	#name : 'BVCLandform',
	#superclass : 'BVCPlugin',
	#category : 'BV-Catalyst-Landform-Core',
	#package : 'BV-Catalyst-Landform-Core'
}

{ #category : 'bounded edit replay' }
BVCLandform >> newBoundedEditReplayFor: recipe payloadResolver: resolver enabledProfiles: enabledProfiles [
 ^ BVCLandformBoundedEditReplay recipe: recipe payloadResolver: resolver enabledProfiles: enabledProfiles
]

{ #category : 'bounded edit replay' }
BVCLandform >> newBoundedEditReplayFor: recipe resources: resources enabledProfiles: enabledProfiles [
 ^ BVCLandformBoundedEditReplay recipe: recipe resources: resources enabledProfiles: enabledProfiles
]
