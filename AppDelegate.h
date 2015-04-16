//
//  AppDelegate.h
//  UKSoundRecorder
//
//  Created by Uli Kusterer on 14.07.07.
//  Copyright 2007 M. Uli Kusterer. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "UKSoundFileRecorder.h"


@interface AppDelegate : NSObject <UKSoundFileRecorderDelegate, NSApplicationDelegate>
@property (weak) IBOutlet UKSoundFileRecorder*	recorder;
@property (weak) IBOutlet NSTextField*			pathField;
@property (weak) IBOutlet NSTextField*			statusField;
@property (weak) IBOutlet NSTextField*			levelField;


@end
