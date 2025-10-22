Class {
	#name : #BVCAINavigationModel,
	#superclass : #Object,
	#category : #'BV-Catalyst-Fairy-Core-Navigation - Model'
}

{ #category : #factory }
BVCAINavigationModel class >> null [
	^ GtCoderNullNavigationModel default
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> classesToShow [
	<return: #Collection of: #Class>
	^ self subclassResponsibility
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> coderDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedClass [
	<return: #Boolean>
	^ self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedPackage [
	<return: #Boolean>
	^ self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedPackageOrClass [
	<return: #Boolean>
	^ self hasSelectedPackage or: [ self hasSelectedClass ]
]

{ #category : #'api - testing' }
BVCAINavigationModel >> hasSelectedTag [
	<return: #Boolean>
	^ self subclassResponsibility
]

{ #category : #'api - testing' }
BVCAINavigationModel >> isNavigationModel [
	^ true
]

{ #category : #'api - accessing' }
BVCAINavigationModel >> packagesToShow [
	<return: #Collection of: #Package>
	^ self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectClass: aClass [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectClasses: aCollectionOfClasses [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectMethod: aCompiledMethod [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectMethods: aCollectionOfCompiledMethods [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectPackage: aPackage [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectedClassDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectedPackageDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - selection' }
BVCAINavigationModel >> selectedTagDo: aBlock [
	self subclassResponsibility
]

{ #category : #'api - subscriptions' }
BVCAINavigationModel >> subscribeToSystem [
	"concrete models can subscribe to the system"
]

{ #category : #'api - subscriptions' }
BVCAINavigationModel >> unsubscribeFromSystem [
	"concrete models can unsubscribe from the system"
]
