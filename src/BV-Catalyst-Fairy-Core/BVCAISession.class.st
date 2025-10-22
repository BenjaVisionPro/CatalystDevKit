Class {
	#name : #BVCAISession,
	#superclass : #Object,
	#instVars : [
		'id',
		'repoPath',
		'branchName',
		'plan',
		'evidence',
		'buildHistory',
		'chatByRole',
		'title',
		'goal',
		'status',
		'dateCreated',
		'dateLastUsed',
		'notes',
		'tags'
	],
	#category : #'BV-Catalyst-Fairy-Core-AI'
}

{ #category : #accessing }
BVCAISession >> branchName [
	^ branchName
]

{ #category : #accessing }
BVCAISession >> branchName: anObject [
	branchName := anObject
]

{ #category : #accessing }
BVCAISession >> buildHistory [
	^ buildHistory
]

{ #category : #'as yet unclassified' }
BVCAISession >> chatAt: aRole ifAbsentPut: aBlock [
	^ chatByRole at: aRole ifAbsentPut: aBlock
]

{ #category : #accessing }
BVCAISession >> dateCreated [
	^ dateCreated
]

{ #category : #accessing }
BVCAISession >> dateLastUsed [
	^ dateLastUsed
]

{ #category : #accessing }
BVCAISession >> dateLastUsed: anObject [
	^ dateLastUsed := anObject
]

{ #category : #accessing }
BVCAISession >> evidence [
	^ evidence
]

{ #category : #accessing }
BVCAISession >> evidence: anObject [
	evidence := anObject
]

{ #category : #accessing }
BVCAISession >> goal [
	^ goal
]

{ #category : #accessing }
BVCAISession >> goal: anObject [
	goal := anObject
]

{ #category : #'as yet unclassified' }
BVCAISession >> gtSummaryFor: aView [
  <gtView>
  ^ aView columnedList
    title: 'Summary';
    items: [ {
      'Title'      -> self title.
      'Goal'       -> self goal.
      'Status'     -> self status.
      'Branch'     -> (self branchName ifNil: [ '—' ]).
      'Repository' -> (self repoPath ifNil: [ '—' ]).
      'Created'    -> self dateCreated.
      'Last used'  -> self dateLastUsed } ];
    column: 'Field' text: [ :assoc | assoc key ];
    column: 'Value' text: [ :assoc | assoc value asString ].
]

{ #category : #'as yet unclassified' }
BVCAISession >> initialize [
	super initialize.
	chatByRole := Dictionary new.
	dateCreated := dateLastUsed := DateAndTime now.
	title := 'Untitled Session'.
	buildHistory := OrderedCollection new
]

{ #category : #accessing }
BVCAISession >> plan [
	^ plan
]

{ #category : #accessing }
BVCAISession >> plan: anObject [
	plan := anObject
]

{ #category : #accessing }
BVCAISession >> repoPath [
	^ repoPath
]

{ #category : #accessing }
BVCAISession >> repoPath: anObject [
	repoPath := anObject
]

{ #category : #accessing }
BVCAISession >> status [
	^ status
]

{ #category : #accessing }
BVCAISession >> status: anObject [
	status := anObject
]

{ #category : #accessing }
BVCAISession >> title [
	^ title
]

{ #category : #accessing }
BVCAISession >> title: anObject [
	title := anObject
]
