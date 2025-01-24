"
I am just a convenience class for creating an example of a full set of gameplay tags. See BVCGamePlayTags-#tagRoot
"
Class {
	#name : #BVCGamePlayTags,
	#superclass : #Object,
	#category : #'BV-Catalyst-UE-Core'
}

{ #category : #examples }
BVCGamePlayTags class >> attributesDefensiveResistanceTagRoot [
	^ (BVCGamePlayTag tag: 'Resistance')
		addChild: (BVCGamePlayTag tag: 'BleedResistance');
		addChild: (BVCGamePlayTag tag: 'BlindDeafResistance');
		addChild: (BVCGamePlayTag tag: 'BurnResistance');
		addChild: (BVCGamePlayTag tag: 'CriticalChanceResistance');
		addChild: (BVCGamePlayTag tag: 'DisorientResistance');
		addChild: (BVCGamePlayTag tag: 'DisruptResistance');
		addChild: (BVCGamePlayTag tag: 'EnsnareResistance');
		addChild: (BVCGamePlayTag tag: 'PoisonResistance');
		addChild: (BVCGamePlayTag tag: 'ShockResistance');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesDefensiveStaminaTagRoot [
	^ (BVCGamePlayTag tag: 'Stamina')
		addChild: (BVCGamePlayTag tag: 'ArmourPerSecondRegeneration');
		addChild: (BVCGamePlayTag tag: 'ArmourOnKill');
		addChild: (BVCGamePlayTag tag: 'HealthRegen');
		addChild: (BVCGamePlayTag tag: 'ExtraIncomingHealth');
		addChild: (BVCGamePlayTag tag: 'SkillHealth');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesDefensiveTagRoot [
	^ (BVCGamePlayTag tag: 'Defensive')
		addChild: self coreDefensiveStaminaTagRoot;
		addChild: self coreDefensiveResistanceTagRoot;
		addChild: self coreDefensiveMendingTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesOffensiveCriticalTagRoot [
	^ (BVCGamePlayTag tag: 'Critical')
		addChild: (BVCGamePlayTag tag: 'AssaultRifleCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'AssaultRifleCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'LightMachinegunCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'LightMachinegunCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'MarksmanRifleCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'MarksmanRifleCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'PistolCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'PistolCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'RifleCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'RifleCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'ShotgunCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'ShotgunCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'SubmachineGunCriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'SubmachineGunCriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'CriticalRange');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesOffensiveDexterityTagRoot [
	^ (BVCGamePlayTag tag: 'Dexterity')
		addChild: (BVCGamePlayTag tag: 'WeaponHandling');
		addChild: (BVCGamePlayTag tag: 'CriticalRange');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesOffensiveFirearmsTagRoot [
	^ (BVCGamePlayTag tag: 'Firearms')
		addChild: (BVCGamePlayTag tag: 'AssaultRifleDamage');
		addChild: (BVCGamePlayTag tag: 'SubmachineGunDamage');
		addChild: (BVCGamePlayTag tag: 'LightMachinegunDamage');
		addChild: (BVCGamePlayTag tag: 'RifleDamage');
		addChild: (BVCGamePlayTag tag: 'MarksmanRifleDamage');
		addChild: (BVCGamePlayTag tag: 'ShotgunDamage');
		addChild: (BVCGamePlayTag tag: 'PistolDamage');
		addChild: (BVCGamePlayTag tag: 'DamageToArmor');
		addChild: (BVCGamePlayTag tag: 'DamageToHealth');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesOffensivePrecisionTagRoot [
	^ (BVCGamePlayTag tag: 'Precision')
		addChild: (BVCGamePlayTag tag: 'HeadshotDamage');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesOffensiveTagRoot [
	^ (BVCGamePlayTag tag: 'Offensive')
		addChild: self attributesOffensiveCriticalTagRoot;
		addChild: self attributesOffensiveFirearmsTagRoot;
		addChild: self attributesOffensivePrecisionTagRoot;
		addChild: self attributesOffensiveDexterityTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesTagRoot [
	^ (BVCGamePlayTag tag: 'Attributes')
		addChild: self attributesOffensiveTagRoot;
		addChild: self attributesDefensiveTagRoot;
		"addChild: self attributesUtilityTagRoot;
		addChild: self attributesReputationTagRoot;
		addChild: self attributesFarmTagRoot;
		addChild: self attributesCraftTagRoot;
		addChild: self attributesManufactureTagRoot;
		addChild: self attributesBuildTagRoot;"
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesUtilityAssistTagRoot [
	^ (BVCGamePlayTag tag: 'Assist')
		addChild: (BVCGamePlayTag tag: 'ReloadSpeed');
		addChild: (BVCGamePlayTag tag: 'IncreasedKillXP');
		addChild: (BVCGamePlayTag tag: 'HeadshotKillXP');
		addChild: (BVCGamePlayTag tag: 'WeakspotKillXP');
		addChild: (BVCGamePlayTag tag: 'BleedDuration');
		addChild: (BVCGamePlayTag tag: 'BlindDuration');
		addChild: (BVCGamePlayTag tag: 'BurnDuration');
		addChild: (BVCGamePlayTag tag: 'ConfuseDuration');
		addChild: (BVCGamePlayTag tag: 'DisruptDuration');
		addChild: (BVCGamePlayTag tag: 'EnsnareDuration');
		addChild: (BVCGamePlayTag tag: 'ShockDuration');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesUtilityElectronicsTagRoot [
	^ (BVCGamePlayTag tag: 'Electronics')
		addChild: (BVCGamePlayTag tag: 'ExtraOutgoingHealing');
		addChild: (BVCGamePlayTag tag: 'ChemLauncherSkillPower');
		addChild: (BVCGamePlayTag tag: 'DroneSkillPower');
		addChild: (BVCGamePlayTag tag: 'FireflySkillPower');
		addChild: (BVCGamePlayTag tag: 'HiveSkillPower');
		addChild: (BVCGamePlayTag tag: 'PulseSkillPower');
		addChild: (BVCGamePlayTag tag: 'SeekerSkillPower');
		addChild: (BVCGamePlayTag tag: 'ShieldSkillPower');
		addChild: (BVCGamePlayTag tag: 'TurretSkillPower');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesUtilityIntensityTagRoot [
	^ (BVCGamePlayTag tag: 'Intensity')
		addChild: (BVCGamePlayTag tag: 'BleedDamage');
		addChild: (BVCGamePlayTag tag: 'BurnDamage');
		addChild: (BVCGamePlayTag tag: 'BleedDuration');
		addChild: (BVCGamePlayTag tag: 'BlindDuration');
		addChild: (BVCGamePlayTag tag: 'BurnDuration');
		addChild: (BVCGamePlayTag tag: 'ConfuseDuration');
		addChild: (BVCGamePlayTag tag: 'DisruptDuration');
		addChild: (BVCGamePlayTag tag: 'EnsnareDuration');
		addChild: (BVCGamePlayTag tag: 'ShockDuration');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesUtilityRepositoryTagRoot [
	^ (BVCGamePlayTag tag: 'Repository')
		addChild: (BVCGamePlayTag tag: 'ExplosivesDamage');
		addChild: (BVCGamePlayTag tag: 'GrenadeDamage');
		addChild: (BVCGamePlayTag tag: 'IncreasedKillXP');
		addChild: (BVCGamePlayTag tag: 'HeadshotKillXP');
		addChild: (BVCGamePlayTag tag: 'WeakspotKillXP');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> attributesUtilityTagRoot [
	^ (BVCGamePlayTag tag: 'Utility')
		addChild: self attributesUtilityRepositoryTagRoot;
		addChild: self attributesUtilityIntensityTagRoot;
		addChild: self attributesUtilityElectronicsTagRoot;
		addChild: self attributesUtilityAssistTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreDefensiveMendingTagRoot [
	^ (BVCGamePlayTag tag: 'Mending')
		addChild: (BVCGamePlayTag tag: 'BonusArmor');
		addChild: (BVCGamePlayTag tag: 'TotalArmor');
		addChild: (BVCGamePlayTag tag: 'ArmorPerSecondRegeneration');
		addChild: (BVCGamePlayTag tag: 'ArmorOnKill');
		addChild: (BVCGamePlayTag tag: 'HealthRegeneration');
		addChild: (BVCGamePlayTag tag: 'ExplosiveResistance');
		addChild: (BVCGamePlayTag tag: 'ProtectionFromElites');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreDefensiveResistanceTagRoot [
	^ (BVCGamePlayTag tag: 'Resistance')
		addChild: (BVCGamePlayTag tag: 'BleedResistance');
		addChild: (BVCGamePlayTag tag: 'BlindDeafResistance');
		addChild: (BVCGamePlayTag tag: 'BurnResistance');
		addChild: (BVCGamePlayTag tag: 'CriticalChanceResistance');
		addChild: (BVCGamePlayTag tag: 'DisorientResistance');
		addChild: (BVCGamePlayTag tag: 'DisruptResistance');
		addChild: (BVCGamePlayTag tag: 'EnsnareResistance');
		addChild: (BVCGamePlayTag tag: 'PoisonResistance');
		addChild: (BVCGamePlayTag tag: 'ShockResistance');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreDefensiveStaminaTagRoot [
	^ (BVCGamePlayTag tag: 'Stamina')
		addChild: (BVCGamePlayTag tag: 'ArmourPerSecondRegeneration');
		addChild: (BVCGamePlayTag tag: 'ArmourOnKill');
		addChild: (BVCGamePlayTag tag: 'HealthRegen');
		addChild: (BVCGamePlayTag tag: 'ExtraIncomingHealth');
		addChild: (BVCGamePlayTag tag: 'SkillHealth');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreDefensiveTagRoot [
	^ (BVCGamePlayTag tag: 'Defensive')
		addChild: self coreDefensiveStaminaTagRoot;
		addChild: self coreDefensiveResistanceTagRoot;
		addChild: self coreDefensiveMendingTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreOffensiveCriticalTagRoot [
	^ (BVCGamePlayTag tag: 'Critical')
		addChild: (BVCGamePlayTag tag: 'CriticalHitChance');
		addChild: (BVCGamePlayTag tag: 'CriticalHitDamage');
		addChild: (BVCGamePlayTag tag: 'CriticalRange');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreOffensiveDexterityTagRoot [
	^ (BVCGamePlayTag tag: 'Dexterity')
		addChild: (BVCGamePlayTag tag: 'WeaponHandling');
		addChild: (BVCGamePlayTag tag: 'CriticalRange');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreOffensiveFirearmsTagRoot [
	^ (BVCGamePlayTag tag: 'Firearms')
		addChild: (BVCGamePlayTag tag: 'DamageToArmor');
		addChild: (BVCGamePlayTag tag: 'DamageToHealth');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreOffensivePrecisionTagRoot [
	^ (BVCGamePlayTag tag: 'Precision')
		addChild: (BVCGamePlayTag tag: 'HeadshotDamage');
		addChild: (BVCGamePlayTag tag: 'OptimalRange');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreOffensiveTagRoot [
	^ (BVCGamePlayTag tag: 'Offensive')
		addChild: self coreOffensiveCriticalTagRoot;
		addChild: self coreOffensiveFirearmsTagRoot;
		addChild: self coreOffensivePrecisionTagRoot;
		addChild: self coreOffensiveDexterityTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalAdaptabilityTagRoot [
	^ (BVCGamePlayTag tag: 'Adaptability')
		addChild: (BVCGamePlayTag
				tag: 'TemperatureTolerance'
				devComment: 'Ability to endure extreme heat or cold.');
		addChild: (BVCGamePlayTag
				tag: 'AltitudeAdaptation'
				devComment: 'Resilience in high or low-altitude environments.');
		addChild: (BVCGamePlayTag
				tag: 'UrbanMovement'
				devComment: 'Skill in navigating crowded or confined spaces.');
		addChild: (BVCGamePlayTag
				tag: 'WildernessSurvival'
				devComment: 'Proficiency in outdoor physical challenges.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalBaseTagRoot [
	^ (BVCGamePlayTag tag: 'Base')
		addChild: (BVCGamePlayTag
				tag: 'Strength'
				devComment: 'Raw physical power, ability to lift, carry, and overpower.');
		addChild: (BVCGamePlayTag
				tag: 'Dexterity'
				devComment: 'Coordination, agility, and precision in movement.');
		addChild: (BVCGamePlayTag
				tag: 'Endurance'
				devComment: 'Stamina and ability to sustain physical activity.');
		addChild: (BVCGamePlayTag
				tag: 'Flexibility'
				devComment: 'Range of motion and ability to bend or contort.');
		addChild: (BVCGamePlayTag tag: 'Speed' devComment: 'Quickness in movement or reflexes.');
		addChild: (BVCGamePlayTag
				tag: 'Balance'
				devComment: 'Ability to maintain equilibrium and stability.');
		addChild: (BVCGamePlayTag
				tag: 'Resilience'
				devComment: 'Resistance to physical harm or recovery from injury.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalDynamicsTagRoot [
	^ (BVCGamePlayTag tag: 'Dynamics')
		addChild: (BVCGamePlayTag
				tag: 'Reflexes'
				devComment: 'Reaction time to sudden events or threats.');
		addChild: (BVCGamePlayTag
				tag: 'ExplosivePower'
				devComment: 'Ability to deliver sudden bursts of strength or speed.');
		addChild: (BVCGamePlayTag
				tag: 'LungCapacity'
				devComment: 'Endurance in activities requiring sustained breathing.');
		addChild: (BVCGamePlayTag
				tag: 'GripStrength'
				devComment: 'Power and dexterity in the hands.');
		addChild: (BVCGamePlayTag
				tag: 'StaminaRecovery'
				devComment: 'How quickly energy replenishes after exertion.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalFitnessTagRoot [
	^ (BVCGamePlayTag tag: 'Fitness')
		addChild: (BVCGamePlayTag
				tag: 'Vitality'
				devComment: 'Overall physical health and energy levels.');
		addChild: (BVCGamePlayTag
				tag: 'Immunity'
				devComment: 'Resistance to illnesses or physical conditions.');
		addChild: (BVCGamePlayTag
				tag: 'Recovery'
				devComment: 'Speed of healing from fatigue or injury.');
		addChild: (BVCGamePlayTag
				tag: 'PainTolerance'
				devComment: 'Ability to endure physical discomfort or injury.');
		addChild: (BVCGamePlayTag
				tag: 'BodyControl'
				devComment: 'Mastery over body movements (e.g., yoga, martial arts).');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalPresenceTagRoot [
	^ (BVCGamePlayTag tag: 'Presence')
		addChild: (BVCGamePlayTag
				tag: 'Height'
				devComment: 'Influence on physical presence and perception by others.');
		addChild: (BVCGamePlayTag
				tag: 'Build'
				devComment: 'Overall body type (e.g., muscular, lean, stocky) and its impact.');
		addChild: (BVCGamePlayTag
				tag: 'Attractiveness'
				devComment: 'Aesthetic appeal or charm based on physical traits.');
		addChild: (BVCGamePlayTag
				tag: 'Posture'
				devComment: 'How confidently and effectively one carries themselves.');
		addChild: (BVCGamePlayTag
				tag: 'Grooming'
				devComment: 'Maintenance of personal hygiene and visual presentation.');
		addChild: (BVCGamePlayTag
				tag: 'Charisma'
				devComment: 'How physical traits enhance one''s natural magnetism.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalSensoryTagRoot [
	^ (BVCGamePlayTag tag: 'Sensory')
		addChild: (BVCGamePlayTag
				tag: 'Vision'
				devComment: 'Acuity of sight and ability to notice visual details.');
		addChild: (BVCGamePlayTag
				tag: 'Hearing'
				devComment: 'Sensitivity to sound, including subtle tones or whispers.');
		addChild: (BVCGamePlayTag
				tag: 'Smell'
				devComment: 'Strength and acuity of olfactory perception.');
		addChild: (BVCGamePlayTag
				tag: 'Taste'
				devComment: 'Sensitivity to flavors (could influence social roles like cooking).');
		addChild: (BVCGamePlayTag
				tag: 'Touch'
				devComment: 'Sensitivity to physical contact or texture.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalSkillsTagRoot [
	^ (BVCGamePlayTag tag: 'Skills')
		addChild: (BVCGamePlayTag
				tag: 'HandEyeCoordination'
				devComment: 'Precision in tasks requiring fine motor control.');
		addChild: (BVCGamePlayTag
				tag: 'TactileSensitivity'
				devComment: 'Perception through touch or fine motor feedback.');
		addChild: (BVCGamePlayTag tag: 'Climbing' devComment: 'Ability to scale walls or trees.');
		addChild: (BVCGamePlayTag
				tag: 'Swimming'
				devComment: 'Proficiency in water-based movement.');
		addChild: (BVCGamePlayTag
				tag: 'Athletics'
				devComment: 'General proficiency in running, jumping, and throwing.');
		addChild: (BVCGamePlayTag
				tag: 'H2HCombatAbility'
				devComment: 'Skill in hand-to-hand fighting.');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> corePhysicalTagRoot [
	^ (BVCGamePlayTag tag: 'Physical')
		addChild: self corePhysicalBaseTagRoot;
		addChild: self corePhysicalPresenceTagRoot;
		addChild: self corePhysicalSkillsTagRoot;
		addChild: self corePhysicalFitnessTagRoot;
		addChild: self corePhysicalSensoryTagRoot;
		addChild: self corePhysicalAdaptabilityTagRoot;
		addChild: self corePhysicalDynamicsTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreTagRoot [
	^ (BVCGamePlayTag tag: 'Core')
		addChild: self corePhysicalTagRoot;
		addChild: self coreOffensiveTagRoot;
		addChild: self coreDefensiveTagRoot;
		addChild: self coreUtilityTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreUtilityAssistTagRoot [
	^ (BVCGamePlayTag tag: 'Assist')
		addChild: (BVCGamePlayTag tag: 'ReloadSpeed');
		addChild: (BVCGamePlayTag tag: 'IncreasedKillXP');
		addChild: (BVCGamePlayTag tag: 'HeadshotKillXP');
		addChild: (BVCGamePlayTag tag: 'WeakspotKillXP');
		addChild: (BVCGamePlayTag tag: 'BleedDuration');
		addChild: (BVCGamePlayTag tag: 'BlindDuration');
		addChild: (BVCGamePlayTag tag: 'BurnDuration');
		addChild: (BVCGamePlayTag tag: 'ConfuseDuration');
		addChild: (BVCGamePlayTag tag: 'DisruptDuration');
		addChild: (BVCGamePlayTag tag: 'EnsnareDuration');
		addChild: (BVCGamePlayTag tag: 'ShockDuration');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreUtilityElectronicsTagRoot [
	^ (BVCGamePlayTag tag: 'Electronics')
		addChild: (BVCGamePlayTag tag: 'ExtraOutgoingHealing');
		addChild: (BVCGamePlayTag tag: 'ChemLauncherSkillPower');
		addChild: (BVCGamePlayTag tag: 'DroneSkillPower');
		addChild: (BVCGamePlayTag tag: 'FireflySkillPower');
		addChild: (BVCGamePlayTag tag: 'HiveSkillPower');
		addChild: (BVCGamePlayTag tag: 'PulseSkillPower');
		addChild: (BVCGamePlayTag tag: 'SeekerSkillPower');
		addChild: (BVCGamePlayTag tag: 'ShieldSkillPower');
		addChild: (BVCGamePlayTag tag: 'TurretSkillPower');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreUtilityIntensityTagRoot [
	^ (BVCGamePlayTag tag: 'Intensity')
		addChild: (BVCGamePlayTag tag: 'BleedDamage');
		addChild: (BVCGamePlayTag tag: 'BurnDamage');
		addChild: (BVCGamePlayTag tag: 'BleedDuration');
		addChild: (BVCGamePlayTag tag: 'BlindDuration');
		addChild: (BVCGamePlayTag tag: 'BurnDuration');
		addChild: (BVCGamePlayTag tag: 'ConfuseDuration');
		addChild: (BVCGamePlayTag tag: 'DisruptDuration');
		addChild: (BVCGamePlayTag tag: 'EnsnareDuration');
		addChild: (BVCGamePlayTag tag: 'ShockDuration');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreUtilityRepositoryTagRoot [
	^ (BVCGamePlayTag tag: 'Repository')
		addChild: (BVCGamePlayTag tag: 'ExplosivesDamage');
		addChild: (BVCGamePlayTag tag: 'GrenadeDamage');
		addChild: (BVCGamePlayTag tag: 'IncreasedKillXP');
		addChild: (BVCGamePlayTag tag: 'HeadshotKillXP');
		addChild: (BVCGamePlayTag tag: 'WeakspotKillXP');
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> coreUtilityTagRoot [
	^ (BVCGamePlayTag tag: 'Utility')
		addChild: self coreUtilityRepositoryTagRoot;
		addChild: self coreUtilityIntensityTagRoot;
		addChild: self coreUtilityElectronicsTagRoot;
		addChild: self coreUtilityAssistTagRoot;
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> statisticsTagRoot [
	^ (BVCGamePlayTag tag: 'Statistics') 
		yourself
]

{ #category : #examples }
BVCGamePlayTags class >> tagRoot [
	<gtExample>
	^ (BVCGamePlayTag tag: 'TGC')
		addChild: self coreTagRoot;
		addChild: self attributesTagRoot;
		addChild: (BVCGamePlayTag tag: 'Statistics');
		yourself
]
