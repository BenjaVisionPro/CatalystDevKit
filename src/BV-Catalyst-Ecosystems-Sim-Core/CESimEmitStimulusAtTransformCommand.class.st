Class {
  #name : 'CESimEmitStimulusAtTransformCommand',
  #superclass : 'CESimStimulusCommand',
  #instVars : [ 'stimulusType', 'transform', 'intensity' ],
  #category : 'BV-Catalyst-Ecosystems-Sim-Core',
  #package : 'BV-Catalyst-Ecosystems-Sim-Core'
}

{ #category : 'instance creation' }
CESimEmitStimulusAtTransformCommand class >> type: aType transform: aTransform intensity: aNumber [
  ^ self new
    stimulusType: aType;
    transform: aTransform;
    intensity: aNumber;
    yourself
]

{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> stimulusType: aType [ stimulusType := aType ]
{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> transform: aTransform [ transform := aTransform ]
{ #category : 'accessing' }
CESimEmitStimulusAtTransformCommand >> intensity: aNumber [ intensity := aNumber ]

{ #category : 'producing' }
CESimEmitStimulusAtTransformCommand >> produceIntoUpdate: aCESimUpdate inContext: aCESimRunContext [
  aCESimUpdate addEvent: (Dictionary new
    at: #type put: #stimulusEmitted;
    at: #stimulusType put: stimulusType;
    at: #transform put: transform;
    at: #intensity put: intensity;
    at: #tickId put: aCESimRunContext tickId;
    yourself).
]