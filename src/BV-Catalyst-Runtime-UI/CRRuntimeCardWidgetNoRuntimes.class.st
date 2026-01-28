Class {
	#name : 'CRRuntimeCardWidgetNoRuntimes',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-UI',
	#package : 'BV-Catalyst-Runtime-UI'
}

{ #category : 'accessing' }
CRRuntimeCardWidgetNoRuntimes >> displayName [
	"I answer placeholder text shown when there are no runtimes."

	^ 'No runtimes'
]

{ #category : 'accessing' }
CRRuntimeCardWidgetNoRuntimes >> isRunning [
	"I answer false for placeholder rows."

	^ false
]

{ #category : 'accessing' }
CRRuntimeCardWidgetNoRuntimes >> runners [
	"I answer an empty collection for placeholder rows."

	^ #()
]

{ #category : 'accessing' }
CRRuntimeCardWidgetNoRuntimes >> workers [
	"I answer an empty collection for placeholder rows."

	^ #()
]
