Class {
	#name : 'CRWorkerService',
	#superclass : 'Object',
	#category : 'BV-Catalyst-Runtime-Services',
	#package : 'BV-Catalyst-Runtime-Services'
}

{ #category : 'lifecycle' }
CRWorkerService >> installOnWorker: aCRWorker configuration: aServiceConfiguration [
	"Subclasses override. Default no-op."

	^ self
]

{ #category : 'lifecycle' }
CRWorkerService >> uninstallFromWorker: aCRWorker [
	"Subclasses override. Default no-op."

	^ self
]
