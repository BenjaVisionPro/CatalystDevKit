Class {
	#name : #BVCInstaller,
	#superclass : #Object,
	#instVars : [
		'installRoot'
	],
	#category : #'BenjaVision-Catalyst-Setup-Core'
}

{ #category : #installation }
BVCInstaller class >> installInDirectory: fileReference [

^ (self new installRoot: fileReference) install
]

{ #category : #installation }
BVCInstaller >> cloneGsDevKit_stones [
	IceGitClone new 
		url: 'git@github.com:GsDevKit/GsDevKit_stones.git'; 
		location: self stonesDirectory;
		execute
]

{ #category : #accessing }
BVCInstaller >> devKitName [
	^ 'BVCToolKit'
]

{ #category : #accessing }
BVCInstaller >> gitDirectory [
	^ (self installDirectory / 'git' ) ensureCreateDirectory
]

{ #category : #installation }
BVCInstaller >> install [
	self 
		cloneGsDevKit_stones;
		runGsDevKit_stonesInstallScript.
	^ self
]

{ #category : #accessing }
BVCInstaller >> installDirectory [
	^ (installRoot / self devKitName) ensureCreateDirectory
]

{ #category : #accessing }
BVCInstaller >> installRoot: fileReference [ 
	installRoot := fileReference
]

{ #category : #installation }
BVCInstaller >> runGsDevKit_stonesInstallScript [
	OSSUnixSubprocess new 
		environmentAt: 'STONES_HOME' put: self installDirectory fullName;
		environmentAt: 'STONES_DATA_HOME' put: (self installDirectory / 'data') fullName;
		workingDirectory: self stonesDirectory fullName;
		shellCommand: (self stonesDirectory / 'bin' / 'install.sh') fullName; 
		runAndWait
]

{ #category : #accessing }
BVCInstaller >> stonesDirectory [
	^ self gitDirectory / 'GsDevKit_stones' 
]
