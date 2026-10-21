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
BVCFairyCodexExamples >> cancelledRequestDoesNotRetry [
	<gtExample>
	| client http entered process attempts |
	entered := Semaphore new.
	attempts := 0.
	http := BVCFairyCodexHttpClientStub new.
	http postAction: [ entered signal. Semaphore new wait ].
	client := BVCFairyCodexClientStub new httpClient: [ attempts := attempts + 1. http ]; yourself.
	process := [ client post: 'responses' withEntity: Dictionary new ] fork.
	[ self assert: (entered waitTimeoutSeconds: 2) not ] ensure: [ process terminate ].
	self assert: attempts equals: 1.
	self assert: http closeCount equals: 1.
	self assert: client history isEmpty.
	^ http
]

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
BVCFairyCodexExamples >> existingFailedChatInstallsRecoveryVisitor [
	<gtExample>
	| parent provider client history messages error |
	parent := BVCFairyChat new provider: GtLOpenAiCodexProvider new; yourself.
	provider := parent provider.
	client := provider client.
	history := client history.
	messages := parent messages.
	error := GtLErrorMessage freeze: (Error new messageText: 'Controlled prior request failure').
	parent addMessage: error.
	provider model userMessageEndpoint: GtLOpenAiCodexResponsesEndpoint new.
	parent refreshInstructions.
	self assert: parent provider == provider.
	self assert: provider client == client.
	self assert: client history == history.
	self assert: parent messages == messages.
	self assert: parent messages last == error.
	self assert: provider model userMessageEndpoint class equals: BVCFairyResponsesEndpoint.
	self assert: provider model userMessageEndpoint newMessageVisitor class equals: BVCFairyResponsesMessageVisitor.
	self assert: ((provider model userMessageEndpoint newMessageVisitor chatMessage: error) at: 'role') equals: 'assistant'.
	^ parent
]

{ #category : 'examples' }
BVCFairyCodexExamples >> failedResponseRetainsEvidenceWithoutRetry [
	<gtExample>
	| client http body attempts failure |
	body := 'event: response.failed', String lf,
		'data: {"type":"response.failed","response":{"error":{"code":"controlled_failure","message":"Controlled failure"}}}', String lf, String lf.
	attempts := 0.
	http := BVCFairyCodexHttpClientStub new
		response: (ZnResponse ok: (ZnEntity text: body));
		postAction: [ body readStream ];
		yourself.
	client := BVCFairyCodexClientStub new httpClient: [ attempts := attempts + 1. http ]; yourself.
	[ client post: 'responses' withEntity: Dictionary new ] on: Error do: [ :error | failure := error ].
	self assert: failure notNil.
	self assert: (failure isKindOf: BVCFairyInterruptedCodexStream) not.
	self assert: attempts equals: 1.
	self assert: http closeCount equals: 1.
	self assert: client history size equals: 1.
	self assert: client history first response contents equals: body.
	^ client
]

{ #category : 'examples' }
BVCFairyCodexExamples >> interruptedResponseRetriesOnlyCurrentRequest [
	<gtExample>
	| client attempts body request record |
	attempts := OrderedCollection new.
	body := self interruptedToolCallStream.
	request := Dictionary new at: 'input' put: 'Already completed child result'; yourself.
	client := BVCFairyCodexClientStub new
		httpClient: [
			| http payload |
			payload := attempts isEmpty ifTrue: [ body ] ifFalse: [ '{"id":"recovered","output":[]}' ].
			http := BVCFairyCodexHttpClientStub new
				response: (ZnResponse ok: (ZnEntity text: payload));
				postAction: [ payload readStream ];
				yourself.
			attempts add: http.
			http ];
		yourself.
	record := client post: 'responses' withEntity: request.
	self assert: attempts size equals: 2.
	self assert: (attempts allSatisfy: [ :http | http closeCount = 1 ]).
	self assert: client history size equals: 2.
	self assert: client history first result isNil.
	self assert: client history first response contents equals: body.
	self assert: (record result at: 'id') equals: 'recovered'.
	self assert: (record result at: 'output') isEmpty.
	self assert: attempts first request contents equals: attempts last request contents.
	self assert: (request at: 'input') equals: 'Already completed child result'.
	^ client
]

{ #category : 'private' }
BVCFairyCodexExamples >> interruptedToolCallStream [
	^ 'event: response.output_item.added', String lf,
		'data: {"type":"response.output_item.added","item":{"type":"function_call","id":"partial","call_id":"partial-call","name":"compileMethods","arguments":""}}', String lf, String lf,
		'event: response.function_call_arguments.delta', String lf,
		'data: {"type":"response.function_call_arguments.delta","item_id":"partial","delta":"{\"methods\":[]}"}', String lf, String lf
]

{ #category : 'examples' }
BVCFairyCodexExamples >> invalidResponsesRetainEvidenceWithoutRetry [
	<gtExample>
	| checked |
	checked := OrderedCollection new.
	{ '{invalid'.
		'event: error', String lf, 'data: {"type":"error","code":"controlled_failure","message":"Controlled stream error"}', String lf, String lf } do: [ :body |
		| client http attempts failure |
		attempts := 0.
		http := BVCFairyCodexHttpClientStub new
			response: (ZnResponse ok: (ZnEntity text: body));
			postAction: [ body readStream ];
			yourself.
		client := BVCFairyCodexClientStub new httpClient: [ attempts := attempts + 1. http ]; yourself.
		[ client post: 'responses' withEntity: Dictionary new ] on: Error do: [ :error | failure := error ].
		self assert: failure notNil.
		self assert: (failure isKindOf: BVCFairyInterruptedCodexStream) not.
		self assert: attempts equals: 1.
		self assert: http closeCount equals: 1.
		self assert: client history size equals: 1.
		self assert: client history first response contents equals: body.
		checked add: client ].
	^ checked
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
BVCFairyCodexExamples >> repeatedInterruptionRetainsBothAttempts [
	<gtExample>
	| client attempts body failure |
	attempts := OrderedCollection new.
	body := self interruptedToolCallStream.
	client := BVCFairyCodexClientStub new
		httpClient: [
			| http |
			http := BVCFairyCodexHttpClientStub new
				response: (ZnResponse ok: (ZnEntity text: body));
				postAction: [ body readStream ];
				yourself.
			attempts add: http.
			http ];
		yourself.
	[ client post: 'responses' withEntity: Dictionary new ]
		on: BVCFairyInterruptedCodexStream do: [ :error | failure := error ].
	self assert: failure notNil.
	self assert: attempts size equals: 2.
	self assert: (attempts allSatisfy: [ :http | http closeCount = 1 ]).
	self assert: client history size equals: 2.
	self assert: failure requestResponse == client history last.
	self assert: (client history allSatisfy: [ :attempt | attempt result isNil ]).
	^ failure
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
BVCFairyCodexExamples >> retainedFailureDoesNotPoisonNextRequest [
	<gtExample>
	| error message retained serialized text |
	error := Error new messageText: 'Controlled interrupted request'.
	message := GtLErrorMessage freeze: error.
	retained := message exception.
	serialized := BVCFairyResponsesEndpoint new newMessageVisitor chatMessage: message.
	self assert: (serialized at: 'role') equals: 'assistant'.
	text := ((serialized at: 'content') first at: 'text').
	self assert: (text includesSubstring: 'Controlled interrupted request').
	self assert: (text includesSubstring: 'unverified').
	self assert: message exception == retained.
	self assert: message contentText equals: 'Controlled interrupted request'.
	self assert: GtLOpenAiResponsesEndpoint new newMessageVisitor class equals: GtLOpenAiResponsesMessageVisitor.
	^ serialized
]

{ #category : 'examples' }
BVCFairyCodexExamples >> retainedFailureEvidenceIsBounded [
	<gtExample>
	| message serialized text |
	message := GtLErrorMessage freeze: (Error new messageText: (String new: 10000 withAll: $x)).
	serialized := BVCFairyResponsesEndpoint new newMessageVisitor chatMessage: message.
	text := ((serialized at: 'content') first at: 'text').
	self assert: text size < 1600.
	self assert: (text includesSubstring: '"truncated":true').
	self assert: message contentText size equals: 10000.
	^ serialized
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
