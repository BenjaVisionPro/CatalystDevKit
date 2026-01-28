Class {
	#name : 'CRAnnouncer',
	#superclass : 'Announcer',
	#instVars : [
		'channelPolicy'
	],
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'channels' }
CRAnnouncer class >> auditChannel [
	^ #auditChannel
]

{ #category : 'channels' }
CRAnnouncer class >> debugChannel [
	^ #debugChannel
]

{ #category : 'channels' }
CRAnnouncer class >> defaultEnabledChannels [
	^ Set with: self operationsChannel with: self securityChannel
]

{ #category : 'channels' }
CRAnnouncer class >> operationsChannel [
	^ #operationsChannel
]

{ #category : 'channels' }
CRAnnouncer class >> securityChannel [
	^ #securityChannel
]

{ #category : 'channels' }
CRAnnouncer class >> telemetryChannel [
	^ #telemetryChannel
]

{ #category : 'announcer' }
CRAnnouncer >> announce: anAnnouncement [
	"I gate announcement delivery by channel, then forward to my superclass."

	(channelPolicy shouldDeliver: anAnnouncement) ifFalse: [ ^ anAnnouncement ].

	^ super announce: anAnnouncement
]

{ #category : 'policy - api' }
CRAnnouncer >> disableChannel: aSymbol [
	"I disable the given channel."

	channelPolicy disableChannel: aSymbol
]

{ #category : 'policy - api' }
CRAnnouncer >> enableChannel: aSymbol [
	"I enable the given channel."

	channelPolicy enableChannel: aSymbol
]

{ #category : 'policy - api' }
CRAnnouncer >> enabledChannels [
	"I answer a copy of my enabled channels."

	^ channelPolicy enabledChannels copy
]

{ #category : 'initialization' }
CRAnnouncer >> initialize [
	"I initialise myself with the default channel policy."

	super initialize.
	channelPolicy := CRAnnouncerChannelPolicy
			enabledChannels: self class defaultEnabledChannels
]

{ #category : 'policy - api' }
CRAnnouncer >> isChannelEnabled: aSymbol [
	"I answer whether the given channel is enabled."

	^ channelPolicy isChannelEnabled: aSymbol
]

{ #category : 'policy - api' }
CRAnnouncer >> toggleChannel: aSymbol [
	"I toggle the given channel."

	channelPolicy toggleChannel: aSymbol
]
