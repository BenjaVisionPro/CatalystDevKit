Class {
	#name : #BVCDevKitManagedInstaller,
	#superclass : #BlElement,
	#instVars : [
		'baseDirectory',
		'gsDevKitDirectory',
		'rootDirectory'
	],
	#classInstVars : [
		'instance'
	],
	#category : #'BV-Catalyst-DevKit-Core'
}

{ #category : #accessing }
BVCDevKitManagedInstaller class >> instance [
	^ instance ifNil: [ instance := super new ]
]

{ #category : #accessing }
BVCDevKitManagedInstaller class >> new [
	"This is a singleton so the sole instance is returned"
	^ self instance
]

{ #category : #accessing }
BVCDevKitManagedInstaller class >> resetInstance [
	instance := nil
]

{ #category : #accessing }
BVCDevKitManagedInstaller class >> rootDirectory [
	^ '/opt' asFileReference
]

{ #category : #accessing }
BVCDevKitManagedInstaller >> baseDirectory [
	^ baseDirectory ifNil: [ baseDirectory := self rootDirectory / self baseDirectoryName ]
]

{ #category : #accessing }
BVCDevKitManagedInstaller >> baseDirectoryName [
	^ 'bvcDevKit'
]

{ #category : #accessing }
BVCDevKitManagedInstaller >> gsDevKitDirectory [
	^ gsDevKitDirectory ifNil: [ self baseDirectory / self gsDevKitName ]
]

{ #category : #accessing }
BVCDevKitManagedInstaller >> gsDevKitName [
	^ 'gsDevKit'
]

{ #category : #accessing }
BVCDevKitManagedInstaller >> rootDirectory [
	^ rootDirectory ifNil: [ rootDirectory := self class rootDirectory ]
]
