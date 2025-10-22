Class {
	#name : #BVCAINullNavigationModel,
	#superclass : #BVCAINavigationModel,
	#traits : 'TGtUniqueInstance',
	#classTraits : 'TGtUniqueInstance classTrait',
	#category : #'BV-Catalyst-Fairy-Core-Navigation - Model'
}

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> classesToShow [
	^ #()
]

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> coderDo: aBlock [
	"do nothing"
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> hasSelectedClass [
	^ false
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> hasSelectedPackage [
	^ false
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> hasSelectedTag [
	^ false
]

{ #category : #'api - testing' }
BVCAINullNavigationModel >> isNavigationModel [
	^ false
]

{ #category : #'api - accessing' }
BVCAINullNavigationModel >> packagesToShow [
	^ #()
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectClass: aClass [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectClasses: aCollectionOfClasses [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectMethod: aCompiledMethod [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectMethodProtocol: aMethodProtocol [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectPackage: aPackage [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectedClassDo: aBlock [
	"do nothing"
]

{ #category : #'as yet unclassified' }
BVCAINullNavigationModel >> selectedPackage [
	"Do Nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectedPackageDo: aBlock [
	"do nothing"
]

{ #category : #'api - selection' }
BVCAINullNavigationModel >> selectedTagDo: aBlock [
	"do nothing"
]
