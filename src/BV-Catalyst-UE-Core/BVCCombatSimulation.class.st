"
I simulate combat by testing attributes, gear, and target combinations exhaustively looking for outlier combinations.

The main metric for combat balance is Time To Kill (TTK). It should remain fairly stable regardless of the players gear.

ie. a submachine style weapon (high rate of projectiles with comparatively low damage) should take the same TTK as an equally powered shotgun style weapon (low rate of high damage projectiles), assuming the level and power of the weapons are equal.

The second goal of combat balance is to find outlier builds (either underpowered or overpowered), to enable fine tuning of values to bring balance to as many build combinations as possible.
"
Class {
	#name : #BVCCombatSimulation,
	#superclass : #BVCSimulation,
	#category : #'BV-Catalyst-UE-Core'
}
