//
//  AppDelegate.m
//  UKSoundRecorder
//
//  Created by Uli Kusterer on 14.07.07.
//  Copyright 2007 M. Uli Kusterer. All rights reserved.
//

#import "AppDelegate.h"


@implementation AppDelegate
@synthesize pathField;
@synthesize recorder;
@synthesize statusField;
@synthesize levelField;

-(void)	awakeFromNib
{
	NSString *recPath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent: @"CocoaRecording.m4a"];
	recorder.outputFilePath = recPath;
	[recorder setDelegate: self];
}

-(void)	soundFileRecorderWasStarted: (UKSoundFileRecorder*)sender
{
	[statusField setStringValue: @"Recording…"];
}

-(void)	soundFileRecorder: (UKSoundFileRecorder*)sender reachedDuration: (NSTimeInterval)timeInSeconds
{
	[statusField setStringValue: [NSString stringWithFormat: @"%ld Seconds…", lroundf(timeInSeconds)]];
}

-(void)	soundFileRecorder: (UKSoundFileRecorder*)sender hasAmplitude: (float)level
{
	[levelField setStringValue: [NSString stringWithFormat: @"%f", level]];
}

-(void)	soundFileRecorderWasStopped: (UKSoundFileRecorder*)sender
{
	[statusField setStringValue: @"Ready."];
}

@end
