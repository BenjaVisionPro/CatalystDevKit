Class {
	#name : 'CRAnnouncerChannelPolicy',
	#superclass : 'Object',
	#instVars : [
		'enabledChannels'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'instance creation' }
CRAnnouncerChannelPolicy class >> enabledChannels: aSet [
	"I answer a new policy seeded with the given enabled channels."

	^ self new
		enabledChannels: aSet;
		yourself
]

{ #category : 'channels' }
CRAnnouncerChannelPolicy >> disableChannel: aSymbol [
	"I disable the given channel."

	enabledChannels remove: aSymbol ifAbsent: [  ]
]

{ #category : 'channels' }
CRAnnouncerChannelPolicy >> enableChannel: aSymbol [
	"I enable the given channel."

	enabledChannels add: aSymbol
]

{ #category : 'accessing' }
CRAnnouncerChannelPolicy >> enabledChannels [
	^ enabledChannels
]

{ #category : 'channels' }
CRAnnouncerChannelPolicy >> enabledChannels: anObject [
	enabledChannels := anObject
]

{ #category : 'channels' }
CRAnnouncerChannelPolicy >> isChannelEnabled: aSymbol [
	"I answer whether the given channel is enabled."

	^ enabledChannels includes: aSymbol
]

{ #category : 'gate' }
CRAnnouncerChannelPolicy >> shouldDeliver: anAnnouncement [
	"I answer whether I should deliver the given announcement."

	^ self isChannelEnabled: anAnnouncement class channel
]

{ #category : 'channels' }
CRAnnouncerChannelPolicy >> toggleChannel: aSymbol [
	"I toggle the given channel."

	(self isChannelEnabled: aSymbol)
		ifTrue: [ self disableChannel: aSymbol ]
		ifFalse: [ self enableChannel: aSymbol ]
]
