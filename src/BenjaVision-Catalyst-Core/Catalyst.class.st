"
# Catalyst
Catalyst is a singleton that acts as the single point of access for all Catalyst models.s
"
Class {
	#name : #Catalyst,
	#superclass : #Object,
	#instVars : [
		'plugins'
	],
	#classInstVars : [
		'licence',
		'instance'
	],
	#category : #'BenjaVision-Catalyst-Core'
}

{ #category : #accessing }
Catalyst class >> instance [
	^ instance ifNil: [ instance := super new ]
]

{ #category : #private }
Catalyst class >> licence: aString [ 
	self validateLicence: aString.
	licence := aString
]

{ #category : #private }
Catalyst class >> new [
	^ self shouldNotImplement
]

{ #category : #private }
Catalyst class >> resetInstance [
	instance := nil
]

{ #category : #private }
Catalyst class >> validateLicence: aString [
	"Connect to BenjaVision Licensing Server (BVLS) to validate the licence - throw an error if there is a problem"	
]

{ #category : #initalization }
Catalyst >> initialize [
	plugins := IdentityDictionary new
]
