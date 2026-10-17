"GT directory listing restricted to visible Catalyst documentation."
Class {
	#name : #BVCFairyDirectoryContentsTool,
	#superclass : #GtLMagritteToolForDirectoryContents,
	#category : #'BV-Catalyst-Fairy-Core'
}

{ #category : #accessing }
BVCFairyDirectoryContentsTool >> description [
	^ 'List visible directories and Markdown documents under the registered Catalyst repository paths in Current DevKit context. Read-only. Hidden paths, symbolic links and files larger than 256 KiB are excluded. Use directoryPath, an absolute path string. Then use getFilesContents to read a document.'
]

{ #category : #private }
BVCFairyDirectoryContentsTool >> directoryContentsFor: aPathString [
	| context reference contents |
	context := BVCDevKitContext new.
	reference := aPathString asFileReference.
	(context allowsDocumentDirectory: reference) ifFalse: [
		^ GtLProblemDomainObject new description: 'Directory is outside the Catalyst document scope, hidden, a symbolic link, or unavailable.' ].
	contents := super directoryContentsFor: reference canonicalize fullName.
	contents
		files: (contents files select: [ :file | context allowsDocumentFile: file pathString asFileReference ]);
		directories: (contents directories select: [ :directory | context allowsDocumentDirectory: directory pathString asFileReference ]).
	^ contents
]
