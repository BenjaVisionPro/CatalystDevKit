"GT file reading restricted to Markdown documents in registered Catalyst checkouts."
Class {
	#name : #BVCFairyFileContentsTool,
	#superclass : #GtLMagritteToolForFilesContents,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCFairyFileContentsTool >> description [
	^ 'Read Markdown documents (.md or .markdown), up to 256 KiB each, under registered Catalyst repository paths in Current DevKit context. Read-only. Hidden paths and symbolic links are excluded. Supply filePaths as an array of objects with an absolute pathString. The whole request is rejected if any path is outside scope. Contents use the standard GT base64 format.'
]

{ #category : #private }
BVCFairyFileContentsTool >> privatePerformToolCall: aToolCall inContext: anExecutionContext [
	| context paths |
	context := BVCDevKitContext new.
	paths := aToolCall arguments at: 'filePaths'.
	paths do: [ :path |
		(context allowsDocumentFile: path pathString asFileReference) ifFalse: [
			^ GtLProblemDomainObject new description: 'Only visible Markdown documents up to 256 KiB in registered Catalyst repositories can be read. Symbolic links are excluded.' ] ].
	^ super privatePerformToolCall: aToolCall inContext: anExecutionContext
]

{ #category : #private }
BVCFairyFileContentsTool >> fileContentsFromPathString: aPathReference [
	| reference |
	reference := aPathReference pathString asFileReference.
	(BVCDevKitContext new allowsDocumentFile: reference) ifFalse: [
		^ GtLProblemDomainObject new description: 'File is outside the Catalyst document scope or exceeds 256 KiB.' ].
	^ super fileContentsFromPathString: (GtLFilePathReference new
		pathString: reference canonicalize fullName)
]
