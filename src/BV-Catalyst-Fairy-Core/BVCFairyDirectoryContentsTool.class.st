"
GT directory listing restricted to visible Catalyst documentation.
"
Class {
	#name : 'BVCFairyDirectoryContentsTool',
	#superclass : 'GtLMagritteToolForDirectoryContents',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyDirectoryContentsTool >> description [
	^ 'List visible directories and Markdown documents in registered DevKit projects. Supply directoryPath as a project-relative reference, for example CatalystRuntime/runtime or CatalystDevKit. Host filesystem paths are not accepted or returned. Read-only; hidden paths, symlinks and documents over 256 KiB are excluded. Read returned file references with getFilesContents.'
]

{ #category : 'private' }
BVCFairyDirectoryContentsTool >> directoryContentsFor: aProjectPath [
	| context reference contents |
	context := BVCDevKitContext new.
	reference := context documentReferenceFor: aProjectPath.
	(reference isNil or: [ (context allowsDocumentDirectory: reference) not ]) ifTrue: [
		^ GtLProblemDomainObject new description: 'Use a visible document directory in a registered DevKit project, such as CatalystRuntime/runtime.' ].
	contents := super directoryContentsFor: reference canonicalize fullName.
	contents
		directoryPath: aProjectPath;
		files: (contents files select: [ :file | context allowsDocumentFile: file pathString asFileReference ]);
		directories: (contents directories select: [ :directory | context allowsDocumentDirectory: directory pathString asFileReference ]).
	contents files, contents directories do: [ :entry |
		entry pathString: (context documentPathFor: entry pathString asFileReference) ].
	^ contents
]

{ #category : 'private' }
BVCFairyDirectoryContentsTool >> privatePerformToolCall: aToolCall inContext: anExecutionContext [
	^ self directoryContentsFor: (aToolCall arguments
		at: 'directoryPath'
		ifAbsent: [ '' ])
]
