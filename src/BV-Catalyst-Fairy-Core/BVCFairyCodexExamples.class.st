"
Offline lifecycle examples; distinguish controlled request execution from native socket resource checks.
"
Class {
	#name : 'BVCFairyCodexExamples',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Fairy-Core-Examples',
	#package : 'BV-Catalyst-Fairy-Core',
	#tag : 'Examples'
}

{ #category : 'examples' }
BVCFairyCodexExamples >> completedResponse [
	<gtExample>
	| client httpClient record body |
	body := '{"id":"offline","output":[]}'.
	httpClient := BVCFairyCodexHttpClientStub new.
	httpClient response: (ZnResponse ok: (ZnEntity text: body)).
	httpClient postAction: [ body readStream ].
	client := BVCFairyCodexClientStub new httpClient: httpClient; yourself.
	record := client postOnce: 'responses' withEntity: Dictionary new.
	self assert: httpClient closeCount equals: 1.
	self assert: record response == httpClient response.
	self assert: record response contents equals: body.
	self assert: (record result at: 'id') equals: 'offline'.
	self assert: client history size equals: 1.
	self assert: (record response entity isKindOf: ZnStreamingEntity) not.
	^ record
]

{ #category : 'examples' }
BVCFairyCodexExamples >> nonUnauthorizedFailureDoesNotRetry [
	<gtExample>
	| client httpClient credential failed |
	credential := BVCFairyCodexCredentialStub new.
	httpClient := BVCFairyCodexHttpClientStub new.
	httpClient postAction: [ (ZnHttpUnsuccessful response: (ZnResponse statusCode: 500)) signal ].
	client := BVCFairyCodexClientStub new credential: credential; httpClient: httpClient; yourself.
	failed := false.
	[ client post: 'responses' withEntity: Dictionary new ] on: ZnHttpUnsuccessful do: [ :error | failed := true ].
	self assert: failed.
	self assert: httpClient closeCount equals: 1.
	self assert: credential refreshCount equals: 0.
	^ httpClient
]

{ #category : 'examples' }
BVCFairyCodexExamples >> preservedClientState [
	<gtExample>
	| original replacement |
	original := GtLOpenAiCodexClient new.
	original baseUrl: 'https://offline.invalid' asZnUrl.
	replacement := BVCFairyCodexClient preservingClient: original.
	GtLOpenAiCodexClient allInstVarNames do: [ :slotName |
		self assert: (original instVarNamed: slotName) == (replacement instVarNamed: slotName) ].
	^ replacement
]

{ #category : 'examples' }
BVCFairyCodexExamples >> repeatedNativeSocketResources [
	<gtExample>
	"No network connection or model request: real native TCP socket allocations,
	controlled HTTP post, real Zinc stream/client close."
	| baseline observations |
	baseline := Smalltalk externalObjects count: #notNil.
	observations := OrderedCollection new.
	10 timesRepeat: [
		| socket stream semaphores httpClient client body |
		socket := Socket newTCP.
		[
			semaphores := { socket instVarNamed: 'semaphore'. socket instVarNamed: 'readSemaphore'. socket instVarNamed: 'writeSemaphore' }.
			self assert: (semaphores allSatisfy: [ :semaphore | Smalltalk externalObjects identityIncludes: semaphore ]).
			stream := ZdcSocketStream on: socket.
			httpClient := BVCFairyCodexHttpClientStub new connection: stream; yourself.
			body := '{"output":[]}'.
			httpClient response: (ZnResponse ok: (ZnEntity text: body)); postAction: [ body ].
			client := BVCFairyCodexClientStub new httpClient: httpClient; yourself.
			client postOnce: 'responses' withEntity: Dictionary new.
			self assert: (socket instVarNamed: 'socketHandle') isNil.
			self assert: (semaphores noneSatisfy: [ :semaphore | Smalltalk externalObjects identityIncludes: semaphore ]).
			self assert: (Smalltalk externalObjects count: #notNil) equals: baseline.
			observations add: { httpClient closeCount. (Smalltalk externalObjects count: #notNil) - baseline }
		] ensure: [ socket destroy ] ].
	^ observations
]

{ #category : 'examples' }
BVCFairyCodexExamples >> requestFailuresClose [
	<gtExample>
	| clients |
	clients := OrderedCollection new.
	#(network bodyRead parse missingTerminal history) do: [ :failureStage |
		| client httpClient body failed |
		body := failureStage = #parse ifTrue: [ '{invalid' ] ifFalse: [ failureStage = #missingTerminal ifTrue: [ '' ] ifFalse: [ '{"output":[]}' ] ].
		httpClient := BVCFairyCodexHttpClientStub new.
		httpClient response: (ZnResponse ok: (ZnEntity text: body)).
		httpClient postAction: [ failureStage = #network ifTrue: [ self error: 'Controlled network failure' ].
			failureStage = #bodyRead ifTrue: [ httpClient ] ifFalse: [ body readStream ] ].
		client := BVCFairyCodexClientStub new httpClient: httpClient; yourself.
		failureStage = #history ifTrue: [ client failHistory ].
		failed := false.
		[ client postOnce: 'responses' withEntity: Dictionary new ] on: Error do: [ :error | failed := true ].
		self assert: failed.
		self assert: httpClient closeCount equals: 1.
		clients add: client ].
	^ clients
]

{ #category : 'examples' }
BVCFairyCodexExamples >> rootAndChildInstallation [
	<gtExample>
	| parent provider original child builder ordinary |
	provider := GtLOpenAiCodexProvider new.
	original := provider model client.
	parent := BVCFairyChat new provider: provider; yourself.
	self assert: parent provider == provider.
	self assert: parent provider model client class equals: BVCFairyCodexClient.
	self assert: parent provider model client history == original history.
	builder := BVCFairyAgentBuilder forAgentCreationRequest: BVCFairyExamples new explorerRequest.
	child := builder createAgentForParent: parent.
	self assert: child provider ~~ provider.
	self assert: child provider model ~~ provider model.
	self assert: child provider model client == provider model client.
	ordinary := GtLChat new provider: GtLOpenAiCodexProvider new; yourself.
	self assert: ordinary provider model client class equals: GtLOpenAiCodexClient.
	^ child
]

{ #category : 'examples' }
BVCFairyCodexExamples >> terminationUnwindsRequest [
	<gtExample>
	| client httpClient entered process |
	entered := Semaphore new.
	httpClient := BVCFairyCodexHttpClientStub new.
	httpClient postAction: [ entered signal. Semaphore new wait ].
	client := BVCFairyCodexClientStub new httpClient: httpClient; yourself.
	process := [ client postOnce: 'responses' withEntity: Dictionary new ] fork.
	[ entered wait ] ensure: [ process terminate ].
	self assert: httpClient closeCount equals: 1.
	self assert: client history isEmpty.
	^ httpClient
]

{ #category : 'examples' }
BVCFairyCodexExamples >> unauthorizedRetryClosesEachAttempt [
	<gtExample>
	| client credential clients body record |
	clients := OrderedCollection new.
	body := '{"output":[]}'.
	credential := BVCFairyCodexCredentialStub new.
	client := BVCFairyCodexClientStub new credential: credential; yourself.
	client httpClient: [
		| httpClient |
		httpClient := BVCFairyCodexHttpClientStub new.
		clients add: httpClient.
		httpClient response: (ZnResponse ok: (ZnEntity text: body)).
		httpClient postAction: [
			clients size = 1 ifTrue: [ (ZnHttpUnsuccessful response: ZnResponse unauthorized) signal ].
			body ].
		httpClient ].
	record := client post: 'responses' withEntity: Dictionary new.
	self assert: clients size equals: 2.
	self assert: (clients allSatisfy: [ :httpClient | httpClient closeCount = 1 ]).
	self assert: credential refreshCount equals: 1.
	self assert: client history size equals: 1.
	^ record
]
