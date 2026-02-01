Class {
	#name : 'CRWorkSchedulerTests',
	#superclass : 'TestCase',
	#category : 'BV-Catalyst-Runtime-ExamplesAndTests',
	#package : 'BV-Catalyst-Runtime-ExamplesAndTests'
}

{ #category : 'tests' }
CRWorkSchedulerTests >> test_millisecondsUntilNextDue_isNeverNegative [
	| scheduler schedule |
	scheduler := CRTestWorkScheduler new.

	schedule := (CRRepeatingSchedule
			workUnitFactory: [ CRBlockUnit on: [  ] ]
			key: #heartbeat
			intervalMillis: 10)
			scheduledMillis: 10;
			yourself.

	scheduler addSchedule: schedule.

	scheduler nowMillis: 0.
	self assert: scheduler millisecondsUntilNextDue >= 0.

	scheduler nowMillis: 7.
	self assert: scheduler millisecondsUntilNextDue >= 0.

	scheduler nowMillis: 10.
	self assert: scheduler millisecondsUntilNextDue >= 0.
]

{ #category : 'tests' }
CRWorkSchedulerTests >> test_repeatingScheduleIntervalMillisMustBePositive [
	self
		should: [ (CRRepeatingSchedule
				workUnitFactory: [ CRBlockUnit on: [  ] ]
				key: #heartbeat
				intervalMillis: 0)
				scheduledMillis: 100;
				yourself ]
		raise: Error
]

{ #category : 'tests' }
CRWorkSchedulerTests >> test_repeatingSchedule_dueTimesDoNotDrift [
	| scheduler sink schedule |
	scheduler := CRTestWorkScheduler new.
	sink := CRTestEnqueueSink new.

	schedule := (CRRepeatingSchedule
			workUnitFactory: [ CRBlockUnit on: [  ] ]
			key: #heartbeat
			intervalMillis: 2000)
			scheduledMillis: 100;
			yourself.

	scheduler addSchedule: schedule.	
	
	"At 100: due"
	scheduler nowMillis: 100.
	scheduler scheduleWorkOn: sink.
	self assert: sink size equals: 1.	
	
	"Still in flight -> should not schedule again even if time advanced past next due"
	scheduler nowMillis: 2100.
	scheduler scheduleWorkOn: sink.
	self assert: sink size equals: 1.	
	
	"Mark complete -> next due should be 2100, not 4100 drifted-from-now"
	scheduler noteCompletedKey: #heartbeat.
	scheduler scheduleWorkOn: sink.
	self assert: sink size equals: 2.	
	
	"Complete again -> next due should be 4100"
	scheduler noteCompletedKey: #heartbeat.
	scheduler nowMillis: 4099.
	scheduler scheduleWorkOn: sink.
	self assert: sink size equals: 2.

	scheduler nowMillis: 4100.
	scheduler scheduleWorkOn: sink.
	self assert: sink size equals: 3
]
