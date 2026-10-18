Extension { #name : 'GtLTextSnippetExporter' }

{ #category : '*BV-Catalyst-Fairy-Core' }
GtLTextSnippetExporter >> visitObjectReferenceAnnotation: anObjectReferenceAnnotation [
	"Preserve the reference without resolving a possibly unavailable live object."
	stream nextPutAll: anObjectReferenceAnnotation parent source
]
