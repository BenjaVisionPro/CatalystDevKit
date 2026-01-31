Class {
	#name : 'CRAnnouncement',
	#superclass : 'Announcement',
	#category : 'BV-Catalyst-Runtime-Core',
	#package : 'BV-Catalyst-Runtime-Core'
}

{ #category : 'channels' }
CRAnnouncement class >> channel [
	"I answer the channel for this announcement type."

	^ CRAnnouncementChannel operations
]
