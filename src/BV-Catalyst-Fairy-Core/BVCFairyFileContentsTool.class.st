"
GT file reading restricted to Markdown documents in registered Catalyst checkouts.
"
Class {
	#name : 'BVCFairyFileContentsTool',
	#superclass : 'GtLMagritteToolForFilesContents',
	#category : 'BV-Catalyst-Fairy-Core',
	#package : 'BV-Catalyst-Fairy-Core'
}

{ #category : 'accessing' }
BVCFairyFileContentsTool >> description [
	^ 'Read Markdown documents in registered DevKit projects. Supply filePaths with project-relative pathString values, for example CatalystRuntime/runtime/Runtime-Ownership-and-Vocabulary.md. Host filesystem paths are not accepted or returned. Read-only; visible Markdown documents up to 256 KiB only, with no symlinks. A denied reference rejects the whole request. Contents use standard GT base64 encoding.'
]

{ #category : 'private' }
BVCFairyFileContentsTool >> fileContentsFromPathString: aPathReference [
	| context reference contents |
	context := BVCDevKitContext new.
	reference := context documentReferenceFor: aPathReference pathString.
	(reference isNil or: [ (context allowsDocumentFile: reference) not ]) ifTrue: [
		^ GtLProblemDomainObject new description: 'File is outside the DevKit document scope or exceeds 256 KiB.' ].
	contents := super fileContentsFromPathString: (GtLFilePathReference new pathString: reference canonicalize fullName).
	(contents isKindOf: GtLFileContentsDomainObject) ifTrue: [
		contents path: aPathReference pathString ].
	^ contents
]

{ #category : 'private' }
BVCFairyFileContentsTool >> privatePerformToolCall: aToolCall inContext: anExecutionContext [
	| context paths |
	context := BVCDevKitContext new.
	paths := aToolCall arguments at: 'filePaths'.
	paths do: [ :path |
		| reference |
		reference := context documentReferenceFor: path pathString.
		(reference isNil or: [ (context allowsDocumentFile: reference) not ]) ifTrue: [
			^ GtLProblemDomainObject new description: 'Only visible Markdown document references in registered DevKit projects can be read. Host paths, hidden paths and symlinks are excluded.' ] ].
	^ super privatePerformToolCall: aToolCall inContext: anExecutionContext
]
