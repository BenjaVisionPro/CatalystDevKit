Class {
	#name : #BVCDevKitWorldElement,
	#superclass : #GtWorldElement,
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #defaults }
BVCDevKitWorldElement >> defaultHomeElement [
	^ BVCDevKitHome new
]

{ #category : #defaults }
BVCDevKitWorldElement >> defaultHomeTabIcon [
	^ BVCDevKitVectorIcons icon: #bvcServer size: 32 @ 32
]
