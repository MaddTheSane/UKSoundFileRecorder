//
//  AppDelegate.swift
//  UKSwiftSoundFileRecorder
//
//  Created by C.W. Betts on 4/16/15.
//
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate, UKSoundFileRecorderDelegate {

	@IBOutlet weak var window: NSWindow!
	@IBOutlet weak var recorder:	UKSoundFileRecorder!
	@IBOutlet weak var pathField:	NSTextField!
	@IBOutlet weak var statusField:	NSTextField!

	override func awakeFromNib() {
		super.awakeFromNib()
		var recPath = NSHomeDirectory()
		//.stringByAppendingPathComponent("Documents").stringByAppendingPathComponent("CocoaRecording.m4a")
		for pathcomp in ["Documents", "CocoaRecording.m4a"] {
			recPath = recPath.stringByAppendingPathComponent(pathcomp)
		}
		recorder.outputFilePath = recPath;
		recorder.delegate = self
	}
	
	func applicationDidFinishLaunching(aNotification: NSNotification) {
		// Insert code here to initialize your application
	}

	func applicationWillTerminate(aNotification: NSNotification) {
		// Insert code here to tear down your application
	}

	func soundFileRecorderWasStarted(sender: UKSoundFileRecorder) {
		statusField.stringValue = "Recording…"
	}
	
	func soundFileRecorderWasStopped(sender: UKSoundFileRecorder) {
		statusField.stringValue = "Ready."
	}
	
	func soundFileRecorder(sender: UKSoundFileRecorder, reachedDuration timeInSeconds: NSTimeInterval) {
		let aString = "\(lround(timeInSeconds)) Seconds…"
		statusField.stringValue = aString
	}
}

